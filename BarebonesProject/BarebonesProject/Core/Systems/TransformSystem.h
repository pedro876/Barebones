#pragma once

#include "../ECS/Coordinator.h"
#include "../Components/Transform.h"

namespace Barebones
{
	class TransformSystem : public System
	{
	public:
		void Update()
		{
			for (auto& entity : mEntities)
			{
				auto& transform = Coordinator::GetComponent<Transform>(entity);
			}
		}

		void AddChild(Entity parent, Entity child)
		{

		}

		void RemoveChild(Entity parent, Entity child)
		{

		}
	};
}