//https://e-aakash.github.io/2020/10/02/assimp-build.html
// REMEMBER TO BUILD NOT ONLY ASSIMP, BUT ALSO ZLIB. REMOVE UNIT TESTS AS THEY ARE NOT NECESSARY.

#include "Model.h"

namespace Barebones
{
	Model::Model(std::string path) : Asset(path) {}

	Mesh* Model::GetMesh(unsigned int meshIndex)
	{
		return &meshes[meshIndex];
	}

	void Model::LoadModel()
	{
		//"../Assets/Models/Cube.fbx"
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
			return;
		}

		Entity root = Coordinator::CreateEntity();
		Coordinator::AddComponent<Transform>(root, Transform());
		if (meshes != nullptr) delete[] meshes;
		if (materials != nullptr) delete[] materials;
		materials = new Material[materialCount = scene->mNumMaterials];
		meshes = new Mesh[meshCount = scene->mNumMeshes];

		//directory = path.substr(0, path.find_last_of('/'));

		for (unsigned int i = 0, count = scene->mNumMaterials; i < count; i++)
		{
			aiMaterial* material = scene->mMaterials[i];
			ProcessMaterial(i, material);
		}

		for (unsigned int i = 0, count = scene->mNumMeshes; i < count; i++)
		{
			aiMesh* mesh = scene->mMeshes[i];
			ProcessMesh(i, mesh);
		}
		
		ProcessNode(scene->mRootNode, scene, root);
	}

	void Model::ProcessNode(aiNode* node, const aiScene* scene, Entity parent)
	{
		//std::cout << "node name: " << node->mName.C_Str() << "\n";
		aiVector3D position, rotation, scaling;
		node->mTransformation.Decompose(scaling, rotation, position);

		Entity entity = parent;
		for (unsigned int i = 0, count = node->mNumMeshes; i < count; i++)
		{
			entity = Coordinator::CreateEntity();
			Transform& transform = Coordinator::AddComponent<Transform>(entity, Transform());
			transform.SetLocalPosition(glm::vec3(position.x, position.y, position.z));
			transform.SetLocalRotation(glm::degrees(glm::vec3(rotation.x, rotation.y, rotation.z)));
			transform.SetLocalScale(glm::vec3(scaling.x, scaling.y, scaling.z));
			TransformSystem::AddChild(parent, entity);

			MeshRenderer& meshRenderer = Coordinator::AddComponent<MeshRenderer>(entity, MeshRenderer());
			unsigned int meshIndex = node->mMeshes[i];
			aiMesh* mesh = scene->mMeshes[meshIndex];
			meshRenderer.mesh = &meshes[meshIndex];
			meshRenderer.material = &materials[mesh->mMaterialIndex];
		}

		for (unsigned int i = 0, count = scene->mNumCameras; i < count; i++)
		{
			aiCamera* mCamera = scene->mCameras[i];
			if (node->mName == mCamera->mName)
			{
				ProcessCamera(parent, node);
			}
		}
		
		for (unsigned int i = 0, count = node->mNumChildren; i < count; i++)
		{
			ProcessNode(node->mChildren[i], scene, entity);
		}
	}

	void Model::ProcessCamera(Entity parent, aiNode* node)
	{
		aiVector3D position, rotation, scaling;
		node->mTransformation.Decompose(scaling, rotation, position);
		Entity entity = Coordinator::CreateEntity();
		glm::quat quat(glm::vec3(rotation.x, rotation.y, rotation.z));
		quat *= glm::quat(glm::radians(glm::vec3(0.0f, -90.0f, 0.0f)));
		Transform& transform = Coordinator::AddComponent<Transform>(entity, Transform());
		transform.SetLocalPosition(glm::vec3(position.x, position.y, position.z));
		transform.SetLocalRotation(quat);
		transform.SetLocalScale(glm::vec3(scaling.x, scaling.y, scaling.z));
		TransformSystem::AddChild(parent, entity);

		Camera& camera = Coordinator::AddComponent<Camera>(entity, Camera());
		//camera.far = mCamera->mClipPlaneFar;
		//camera.near = mCamera->mClipPlaneNear;
		//camera.fieldOfView = mCamera->mHorizontalFOV;
		camera.priority = 1;
	}

	void Model::ProcessMaterial(unsigned int index, aiMaterial* material)
	{
		materials[index].shader = DB<Shader>::Get("Default Shader");
		materials[index].name = material->GetName().C_Str();

		std::cout << material->GetName().C_Str() << std::endl;

		for (unsigned int t = 0, textureCount = material->GetTextureCount(aiTextureType_DIFFUSE); t < textureCount; t++)
		{
			aiString ogPath;
			if (material->GetTexture(aiTextureType_DIFFUSE, t, &ogPath) == AI_SUCCESS)
			{
				std::string relativePath = File::MakeRelativeToFileBeRelativeToCWD(path, ogPath.C_Str()).string();
				std::cout << "Texture path (" << ogPath.C_Str() << ") was modified to (" << relativePath << ")\n";
				bool wasLoaded = false;
				if (!DB<Texture>::Has(relativePath))
				{
					DB<Texture>::Register(std::make_shared<Texture>(relativePath));
					wasLoaded = true;
				}
				auto texturePtr = DB<Texture>::Get(relativePath);
				if (auto texture = texturePtr.lock())
				{
					if (wasLoaded) texture->Load();
					//materials[index].baseMap = texturePtr;

					Material::Property<std::weak_ptr<Texture>> textureProperty;
					textureProperty.name = "_BaseMap";
					textureProperty.value = texturePtr;
					materials[index].properties_textures.push_back(std::move(textureProperty));
				}

				

			}
		}
	}

	void Model::ProcessMesh(unsigned int index, aiMesh* mesh)
	{
		// Indices
		std::vector<unsigned int> indices;
		for (unsigned int i = 0, count = mesh->mNumFaces; i < count; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (unsigned int j = 0, count = face.mNumIndices; j < count; j++)
			{
				indices.push_back(face.mIndices[j]);
			}
		}

		// Attributes
		unsigned int vertexCount = mesh->mNumVertices;

		std::vector<Vertex> vertices;
		vertices.reserve(vertexCount);
		for (unsigned int i = 0; i < vertexCount; i++)
		{
			aiVector3D vertex = mesh->mVertices[i];
			vertices.push_back(
				Vertex(
					glm::vec3(vertex.x, vertex.y, vertex.z),
					glm::vec3(0.0f, 0.0f, 1.0f)
				)
			);
		}

		if (mesh->HasNormals())
		{
			for (unsigned int i = 0; i < vertexCount; i++)
			{
				aiVector3D normal = mesh->mNormals[i];
				vertices[i].normal = glm::vec3(normal.x, normal.y, normal.z);
			}
		}

		if (mesh->HasTextureCoords(0))
		{
			for (unsigned int i = 0; i < vertexCount; i++)
			{
				aiVector3D texcoord0 = mesh->mTextureCoords[0][i];
				vertices[i].texcoord0 = glm::vec2(texcoord0.x, texcoord0.y);
			}
		}

		meshes[index] = Mesh(mesh->mName.C_Str(), indices, vertices);
	}
}