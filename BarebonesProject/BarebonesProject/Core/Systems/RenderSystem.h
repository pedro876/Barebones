#pragma once

#include "../ECS/Coordinator.h"
#include "../Components/Transform.h"
#include "../Components/MeshRenderer.h"
#include "../GL/GL.h"

#include "CameraSystem.h"

namespace Barebones
{
	class RenderSystem : public System
	{
	public:
		
		void Init();
		void Update(GL& gl, float dt);
		void EntityDestroyed(Entity entity) override;
	};
}

