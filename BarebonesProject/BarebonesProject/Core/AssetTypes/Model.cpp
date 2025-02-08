//https://e-aakash.github.io/2020/10/02/assimp-build.html
// REMEMBER TO BUILD NOT ONLY ASSIMP, BUT ALSO ZLIB. REMOVE UNIT TESTS AS THEY ARE NOT NECESSARY.

#include "Model.h"

namespace Barebones
{
	void Model::loadModel(std::string path)
	{
		//"../Assets/Models/Cube.fbx"
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
			return;
		}

		directory = path.substr(0, path.find_last_of('/'));
		processNode(scene->mRootNode, scene);

	}
	void Model::processNode(aiNode* node, const aiScene* scene)
	{
		for (unsigned int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			meshes.push_back(processMesh(mesh, scene));
		}
		for (unsigned int i = 0; i < node->mNumChildren; i++)
		{
			processNode(node->mChildren[i], scene);
		}
	}

	Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
	{
		// Indices
		std::vector<unsigned int> indices;
		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; j++)
			{
				indices.push_back(face.mIndices[j]);
			}
		}

		// Attributes
		unsigned int vertexCount = mesh->mNumVertices;

		std::vector<glm::vec3> vertices;
		vertices.reserve(vertexCount);
		for (unsigned int i = 0; i < vertexCount; i++)
		{
			aiVector3D vertex = mesh->mVertices[i];
			vertices.push_back(glm::vec3(vertex.x, vertex.y, vertex.z));
		}

		std::vector<glm::vec3> normals;
		if (mesh->HasNormals())
		{
			for (unsigned int i = 0; i < vertexCount; i++)
			{
				aiVector3D normal = mesh->mNormals[i];
				normals.push_back(glm::vec3(normal.x, normal.y, normal.z));
			}
		}

		return Mesh(indices.size(), vertexCount, indices, vertices, normals);
	}
}