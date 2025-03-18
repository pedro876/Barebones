#pragma once

#include "../ECS/Coordinator.h"
#include "../Components/Transform.h"
#include "../Components/Light.h"

namespace Barebones
{
	class LightingSystem : public System
	{
	public:
		
		static inline Entity mainLight{ 0 };
		static inline glm::vec3 ambientLight{ 0.1, 0.1, 0.1 };
		
		LightingSystem()
		{

		}

		void Update(GL& gl, float dt)
		{
			gl.SetAmbientLight(ambientLight);
			int visibleLightIndex = 0;
			for (auto& entity : mEntities)
			{
				if (visibleLightIndex == gl.MAX_LIGHT_COUNT)
				{
					break;
				}
				auto& transform = Coordinator::GetComponent<Transform>(entity);
				auto& light = Coordinator::GetComponent<Light>(entity);
				gl.SetAdditionalLight(visibleLightIndex++, transform, light);
			}
			gl.SetAdditionalLightCount(visibleLightIndex);
		}

		void EntityDestroyed(Entity entity) override
		{

		}
	};
}