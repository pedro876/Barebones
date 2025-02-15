#pragma once

#include "../DB/Model/Material.h"
#include "../DB/Model/Mesh.h"

namespace Barebones
{
	struct MeshRenderer
	{
		Mesh* mesh;
		Material* material;
	};
}