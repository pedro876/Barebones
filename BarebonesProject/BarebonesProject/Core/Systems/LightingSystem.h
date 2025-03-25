#pragma once

#include "../GL/GL.h"
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
		
		LightingSystem();
		Signature CreateSignature() override;
		void Update(float dt);
		void EntityDestroyed(Entity entity) override;

		
	};
}