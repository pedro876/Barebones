#pragma once
#include "../ECS/Coordinator.h"
#include "../ECS/SystemManager.h"
#include "../GL/Input.h"

namespace Barebones
{

	class InputSystem : public System
	{
	public:
		InputSystem()
		{

		}

		Signature CreateSignature() override
		{
			Signature s = 0;
			return s;
		}

		void EntityDestroyed(Entity entity) override
		{

		}
		
		void Update(float dt)
		{
			for (int i = 0; i < inputCount; i++)
			{
				inputs[i].ProcessInput();
			}
		}

		static Input* GetInput(Key key)
		{
			for (int i = 0; i < inputCount; i++)
			{
				if (inputs[i].key == key)
				{
					return &inputs[i];
				}
			}

			inputs[inputCount].SetKey(key);
			return &inputs[inputCount++];
		}

	private:
		static inline unsigned int inputCount = 0;
		static inline Input inputs[100];
	};
}