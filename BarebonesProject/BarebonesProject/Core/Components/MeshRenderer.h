#pragma once

#include "../AssetTypes/Material.h"
#include "../AssetTypes/Mesh.h"

namespace Barebones
{
	struct MeshRenderer
	{
		Mesh* mesh;
		std::weak_ptr<Material> material;
	};
}