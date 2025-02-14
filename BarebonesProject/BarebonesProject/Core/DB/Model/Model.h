#pragma once

#include "Mesh.h"
#include <vector>
#include <string>
#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "../Asset.h"

#include "../../Components/Transform.h"
#include "../../Components/MeshRenderer.h"
#include "../../Components/Camera.h"
#include "../../Systems/TransformSystem.h"

namespace Barebones
{
	class Model : public Asset
	{
	public:
		Model(std::string path);
		Mesh* GetMesh(unsigned int meshIndex);
		unsigned int GetMeshCount() { return meshCount; }
		void LoadModel();

	private:
		Mesh* meshes = nullptr;
		unsigned int meshCount = 0;

		void ProcessNode(aiNode* node, const aiScene* scene, Entity parent);
		Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
	};
}