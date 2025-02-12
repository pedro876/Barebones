#pragma once

#include "Mesh.h"
#include <vector>
#include <string>
#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "../Asset.h"

namespace Barebones
{
	class Model : public Asset
	{
	public:
		Model(std::string path);
		Mesh* GetMesh(unsigned int meshIndex);
		void LoadModel();

	private:
		std::vector<Mesh> meshes;

		void ProcessNode(aiNode* node, const aiScene* scene, unsigned int depth);
		Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
	};
}