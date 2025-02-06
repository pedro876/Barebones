#pragma once

#include "Mesh.h"
#include <vector>
#include <string>
#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Barebones
{
	class Model
	{
	public:
		Model(const char* path)
		{
			loadModel(path);
		}
		Mesh* GetMesh(unsigned int meshIndex)
		{
			return &meshes[meshIndex];
		}
	private:
		std::vector<Mesh> meshes;
		std::string directory;

		void loadModel(std::string path);
		void processNode(aiNode* node, const aiScene* scene);
		Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	};
}