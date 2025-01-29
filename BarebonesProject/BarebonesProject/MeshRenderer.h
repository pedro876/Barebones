#pragma once

#include "Material.h"
#include "Mesh.h"

namespace Barebones
{
	struct MeshRenderer
	{
		Mesh* mesh;
		Material* material;
	};
}