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
		
		Signature CreateSignature() override
		{
			Signature s;
			s.set(Coordinator::GetComponentType<Transform>());
			s.set(Coordinator::GetComponentType<Light>());
			return s;
		}

		LightingSystem()
		{

		}

		void Update(float dt)
		{
			GL::BeginLightSetup();
			GL::SetAmbientLight(ambientLight);
			int visibleLightIndex = 0;
			Entity maxSunIntensityEntity = 0;
			Transform* sunTransform = nullptr;
			Light* sunLight = nullptr;
			float maxSunIntensity = 0.0f;
			for (auto& entity : mEntities)
			{
				if (visibleLightIndex == GL::MAX_LIGHT_COUNT)
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
					GL::SetAdditionalLight(visibleLightIndex++, transform, light);
				}
			}
			mainLight = maxSunIntensityEntity;
			GL::SetDirectionalLight(sunTransform, sunLight);
			GL::SetAdditionalLightCount(visibleLightIndex);
			GL::EndLightSetup();
		}

		void EntityDestroyed(Entity entity) override
		{

		}

		
	};
}