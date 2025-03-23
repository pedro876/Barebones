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
			glfwSetInputMode(GL::window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			glfwSetCursorPosCallback(GL::window, OnMouse);
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

		void EndFrame()
		{
			mouseAxis = glm::vec2(0.0f, 0.0f);
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

		static glm::vec2 GetMouseAxis()
		{
			return mouseAxis;
		}

	private:
		static inline unsigned int inputCount = 0;
		static inline Input inputs[100];
		static inline double lastMouseX;
		static inline double lastMouseY;
		static inline bool everDetectedMouse;
		static inline glm::vec2 mouseAxis;
		static inline const float sensitivity = 0.1f;

		static void OnMouse(GLFWwindow* window, double xpos, double ypos)
		{
			if (!everDetectedMouse)
			{
				everDetectedMouse = true;
				lastMouseX = xpos;
				lastMouseY = ypos;
			}

			mouseAxis = glm::vec2(xpos - lastMouseX, ypos - lastMouseY);
			mouseAxis *= sensitivity;

			lastMouseX = xpos;
			lastMouseY = ypos;
		}
	};
}