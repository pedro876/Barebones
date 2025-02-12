#pragma once

#include "../DB/Material/Material.h"
#include "../DB/Model/Mesh.h"

namespace Barebones
{
	struct MeshRenderer
	{
		Mesh* mesh;
		std::weak_ptr<Material> material;
	};
}