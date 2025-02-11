#pragma once

#include "Mesh.h"
#include <vector>
#include <string>
#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Asset.h"

namespace Barebones
{
	class Model : public Asset
	{
	public:
		Model(std::string directory, std::string name);
		Mesh* GetMesh(unsigned int meshIndex);
		void LoadModel();

	private:
		std::vector<Mesh> meshes;
		std::string directory;
		std::string name;
		std::string path;

		void ProcessNode(aiNode* node, const aiScene* scene);
		Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
	};
}