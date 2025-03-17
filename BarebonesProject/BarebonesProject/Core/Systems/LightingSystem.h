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
		
		void Update(float dt)
		{

		}

		void EntityDestroyed(Entity entity) override
		{

		}
	};
}