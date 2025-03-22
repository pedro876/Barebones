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
			gl.BeginLightSetup();
			gl.SetAmbientLight(ambientLight);
			int visibleLightIndex = 0;
			Entity maxSunIntensityEntity = 0;
			Transform* sunTransform = nullptr;
			Light* sunLight = nullptr;
			float maxSunIntensity = 0.0f;
			for (auto& entity : mEntities)
			{
				if (visibleLightIndex == gl.MAX_LIGHT_COUNT)
				{
					break;
				}
				auto& transform = Coordinator::GetComponent<Transform>(entity);
				auto& light = Coordinator::GetComponent<Light>(entity);

				if (light.type == LightType::Directional)
				{
					if (light.intensity > maxSunIntensity)
					{
						maxSunIntensity = light.intensity;
						maxSunIntensityEntity = entity;
						sunTransform = &transform;
						sunLight = &light;
					}
				}
				else
				{
					gl.SetAdditionalLight(visibleLightIndex++, transform, light);
				}
			}
			mainLight = maxSunIntensityEntity;
			gl.SetDirectionalLight(sunTransform, sunLight);
			gl.SetAdditionalLightCount(visibleLightIndex);
			gl.EndLightSetup();
		}

		void EntityDestroyed(Entity entity) override
		{

		}
	};
}