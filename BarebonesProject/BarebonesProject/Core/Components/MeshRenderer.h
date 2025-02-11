#pragma once

#include "../AssetTypes/Material/Material.h"
#include "../AssetTypes/Model/Mesh.h"

namespace Barebones
{
	struct MeshRenderer
	{
		Mesh* mesh;
		std::weak_ptr<Material> material;
	};
}