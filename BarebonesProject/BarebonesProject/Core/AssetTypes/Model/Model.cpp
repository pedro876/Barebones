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

		//directory = path.substr(0, path.find_last_of('/'));

		for (unsigned int i = 0, count = scene->mNumMaterials; i < count; i++)
		{
			aiMaterial* material = scene->mMaterials[i];
			std::cout << material->GetName().C_Str() << std::endl;

			for (unsigned int t = 0, textureCount = material->GetTextureCount(aiTextureType_DIFFUSE); t < textureCount; t++)
			{
				aiString path;
				if (material->GetTexture(aiTextureType_DIFFUSE, t, &path) == AI_SUCCESS)
				{
					std::cout << path.C_Str() << std::endl;
				}
			}
		}

		for (unsigned int i = 0, count = scene->mNumCameras; i < count; i++)
		{
			aiCamera* camera = scene->mCameras[i];
			aiNode* cameraNode = scene->mRootNode->FindNode(camera->mName);

			if (cameraNode)
			{
				aiVector3D scaling, rotation, position;
				cameraNode->mTransformation.Decompose(scaling, rotation, position);

				glm::vec3 cameraPos = glm::vec3(position.x, position.y, position.z);
				std::cout << "Camera position: " << cameraPos.x << " " << cameraPos.y << " " << cameraPos.z << std::endl;
			}
		}

		ProcessNode(scene->mRootNode, scene, 0);
	}

	void Model::ProcessNode(aiNode* node, const aiScene* scene, unsigned int depth)
	{
		for (unsigned int i = 0, count = node->mNumMeshes; i < count; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			meshes.push_back(ProcessMesh(mesh, scene));
		}
		for (unsigned int i = 0, count = node->mNumChildren; i < count; i++)
		{
			ProcessNode(node->mChildren[i], scene, depth+1);
		}
	}

	Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
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

		return Mesh(mesh->mName.C_Str(), indices, vertices);
	}
}