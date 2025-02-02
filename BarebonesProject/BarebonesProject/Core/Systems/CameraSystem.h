#pragma once

#include "../ECS/Coordinator.h"
#include "../Components/Transform.h"
#include "../Components/Camera.h"

namespace Barebones
{
	class CameraSystem : public System
	{
	public:
		static Entity mainCamera;
		static glm::mat4 mainViewProj;
		void Update(Coordinator& coordinator, float dt);
	};
}