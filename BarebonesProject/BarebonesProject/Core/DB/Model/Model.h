#pragma once


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
#include "Mesh.h"
#include "Material.h"
#include "../Texture/Texture.h"

namespace Barebones
{
	class Model : public Asset
	{
	public:
		Model(std::string path);
		Mesh* GetMesh(unsigned int meshIndex);
		unsigned int GetMeshCount() { return meshCount; }
		unsigned int GetMaterialCount() { return materialCount; }
		void LoadModel();

	private:
		Mesh* meshes = nullptr;
		Material* materials = nullptr;
		unsigned int meshCount = 0;
		unsigned int materialCount = 0;

		void ProcessNode(aiNode* node, const aiScene* scene, Entity parent);
		void ProcessCamera(Entity parent, aiNode* node);
		void ProcessMaterial(unsigned int index, aiMaterial* material);
		void ProcessMesh(unsigned int index, aiMesh* mesh);
	};
}