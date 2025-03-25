#pragma once

#include "../DB/Model/Material.h"
#include "../DB/Model/Mesh.h"
#include <vector>

namespace Barebones
{
	struct MeshRenderer
	{
	public:
		std::vector<Mesh*> meshes;
		std::vector<Material*> materials;
		int meshCount;

		MeshRenderer(int meshCount = 0) : 
			meshCount(meshCount), 
			materials(meshCount, nullptr), 
			meshes(meshCount, nullptr)
		{
			
		}
	};
}