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
			aiMaterial* mMaterial = scene->mMaterials[i];
			ProcessMaterial(i, mMaterial);
		}

		for (unsigned int i = 0, count = scene->mNumMeshes; i < count; i++)
		{
			aiMesh* mMesh = scene->mMeshes[i];
			ProcessMesh(i, mMesh);
		}

		std::filesystem::path lightsPath = path;
		lightsPath.replace_extension(".lights");

		std::vector<std::string> lightsCSV;
		if (File::Exists(lightsPath))
		{
			lightsCSV = File::ReadLines(lightsPath);
		}
		
		ProcessNode(scene->mRootNode, scene, root, lightsCSV);
	}

	void Model::ProcessNode(aiNode* mNode, const aiScene* mScene, Entity parent, const std::vector<std::string>& lightsCSV)
	{
		//std::cout << "node name: " << node->mName.C_Str() << "\n";
		aiVector3D position, rotation, scaling;
		mNode->mTransformation.Decompose(scaling, rotation, position);

		Entity entity = Coordinator::CreateEntity();

		if (mNode->mNumMeshes)
		{
			MeshRenderer& meshRenderer = Coordinator::AddComponent<MeshRenderer>(entity, MeshRenderer(mNode->mNumMeshes));

			for (unsigned int i = 0, count = mNode->mNumMeshes; i < count; i++)
			{
				unsigned int meshIndex = mNode->mMeshes[i];
				aiMesh* mesh = mScene->mMeshes[meshIndex];
				meshRenderer.meshes[i] = &meshes[meshIndex];
				meshRenderer.materials[i] = &materials[mesh->mMaterialIndex];
			}
		}

		bool isCamera = false;
		for (unsigned int i = 0, count = mScene->mNumCameras; i < count; i++)
		{
			aiCamera* mCamera = mScene->mCameras[i];
			if (mNode->mName == mCamera->mName)
			{
				isCamera = true;
				ProcessCamera(entity, mNode, mCamera);
				break;
			}
		}

		for (unsigned int i = 0, count = mScene->mNumLights; i < count; i++)
		{
			aiLight* mLight = mScene->mLights[i];
			if (mNode->mName == mLight->mName)
			{
				ProcessLight(entity, mNode, mLight, lightsCSV);
				break;
			}
		}

		Transform& transform = Coordinator::AddComponent<Transform>(entity, Transform());
		transform.SetLocalPosition(glm::vec3(position.x, position.y, position.z));
		glm::quat quat(glm::vec3(rotation.x, rotation.y, rotation.z));
		if(isCamera) quat *= glm::quat(glm::radians(glm::vec3(0.0f, -90.0f, 0.0f)));
		transform.SetLocalRotation(quat);
		transform.SetLocalScale(glm::vec3(scaling.x, scaling.y, scaling.z));
		TransformSystem::AddChild(parent, entity);
		
		for (unsigned int i = 0, count = mNode->mNumChildren; i < count; i++)
		{
			ProcessNode(mNode->mChildren[i], mScene, entity, lightsCSV);
		}
	}

	void Model::ProcessLight(Entity entity, aiNode* mNode, aiLight* mLight, const std::vector<std::string>& lightsCSV)
	{
		//We need to find the csv data here
		bool foundLightData = false;
		Light light;
		for (int i = 1, count = lightsCSV.size(); i < count && !foundLightData; i++)
		{
			if (lightsCSV[i].starts_with(mNode->mName.C_Str()))
			{
				foundLightData = true;
				std::vector<std::string> tokens = File::SplitLine(lightsCSV[i], ';');
				light.range = std::stof(tokens[1]);
				light.intensity = std::stof(tokens[2]);
				light.color = glm::vec3(std::stof(tokens[3]), std::stof(tokens[4]), std::stof(tokens[5]));
			}
		}

		if (mLight->mType == aiLightSourceType::aiLightSource_POINT) light.type = LightType::Point;
		if (mLight->mType == aiLightSourceType::aiLightSource_DIRECTIONAL) light.type = LightType::Directional;
		if (mLight->mType == aiLightSourceType::aiLightSource_SPOT) light.type = LightType::Spot;
		if (mLight->mType == aiLightSourceType::aiLightSource_AREA) light.type = LightType::Area;

		light.outerConeAngle = glm::degrees(mLight->mAngleOuterCone);
		light.innerConeAngle = glm::degrees(mLight->mAngleInnerCone);

		Coordinator::AddComponent<Light>(entity, light);
	}

	void Model::ProcessCamera(Entity entity, aiNode* mNode, aiCamera* mCamera)
	{
		Camera& camera = Coordinator::AddComponent<Camera>(entity, Camera());
		camera.priority = 1;
	}

	void Model::ProcessMaterial(unsigned int index, aiMaterial* mMaterial)
	{
		materials[index].shader = DB<Shader>::Get("Shader Lit");
		materials[index].name = mMaterial->GetName().C_Str();

		std::cout << "Processing material " << mMaterial->GetName().C_Str() << std::endl;

		for (unsigned int t = 0, textureCount = mMaterial->GetTextureCount(aiTextureType_DIFFUSE); t < textureCount; t++)
		{
			aiString ogPath;
			if (mMaterial->GetTexture(aiTextureType_DIFFUSE, t, &ogPath) == AI_SUCCESS)
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

					/*Material::Property<std::weak_ptr<Texture>> textureProperty("_BaseMap", texturePtr);
					textureProperty.name = "_BaseMap";
					textureProperty.value = texturePtr;*/
					materials[index].properties.textures.emplace_back(
						Property<std::weak_ptr<Texture>>("_BaseMap", texturePtr)
					);
				}
			}
		}

		std::filesystem::path materialPath = directory;
		materialPath = materialPath / mMaterial->GetName().C_Str() += ".mat";
		materialPath = materialPath.lexically_normal();

		if (File::Exists(materialPath))
		{
			std::vector<std::string> lines = File::ReadLines(materialPath);
			Material& m = materials[index];
			for (std::string& line : lines)
			{
				m.properties.AddSerializedPropertyCSV(line);

				std::cout << line << "\n";
			}
		}

		/*std::cout << "***************\n";
		std::cout << "Material: " << material->GetName().C_Str() << "\n";
		for (unsigned int i = 0, propertyCount = material->mNumProperties; i < propertyCount; i++)
		{
			aiMaterialProperty& property = *material->mProperties[i];

			std::cout << "prop " << property.mKey.C_Str() << 
				" with idx " << property.mIndex << " and type " << property.mType << "\n";
		}
		std::cout << "***************\n";*/
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