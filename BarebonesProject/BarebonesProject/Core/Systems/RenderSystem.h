#pragma once

#include "../ECS/Coordinator.h"
#include "../Components/Transform.h"
#include "../Components/MeshRenderer.h"
#include "../GL/GL.h"

namespace Barebones
{
	class RenderSystem : public System
	{
	public:
		
		void Init();
		void Update(Coordinator& coordinator, GL& gl, float dt);
	};
}

