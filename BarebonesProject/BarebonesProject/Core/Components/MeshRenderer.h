#pragma once

#include "../AssetTypes/Material.h"
#include "../AssetTypes/Mesh.h"

namespace Barebones
{
	struct MeshRenderer
	{
		Mesh* mesh;
		Material* material;
	};
}