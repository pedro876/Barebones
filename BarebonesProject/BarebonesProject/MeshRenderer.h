#pragma once

#include "Component.h"
#include "Mesh.h"
#include "Material.h"

namespace Barebones
{
	class MeshRenderer : public Component
	{
	public:
		Mesh* mesh = nullptr;
		Material* material = nullptr;
	};
}

