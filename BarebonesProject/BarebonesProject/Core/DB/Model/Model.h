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
#include "../../Components/Light.h"
#include "../../Systems/TransformSystem.h"
#include "Mesh.h"
#include "Material.h"
#include "../Shader/PropertyBlock.h"
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

		void ProcessNode(aiNode* mNode, const aiScene* mScene, Entity parent, const std::vector<std::string>& lightsCSV);
		void ProcessLight(Entity parent, aiNode* mNode, aiLight* mLight, const std::vector<std::string>& lightsCSV);
		void ProcessCamera(Entity parent, aiNode* mNode, aiCamera* mCamera);
		void ProcessMaterial(unsigned int index, aiMaterial* mMaterial);
		void ProcessTexture(unsigned int index, aiMaterial* mMaterial, aiTextureType textureType, std::string propertyName);
		void ProcessMesh(unsigned int index, aiMesh* mesh);
	};
}