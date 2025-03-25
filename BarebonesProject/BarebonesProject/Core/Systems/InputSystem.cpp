#include "InputSystem.h"

namespace Barebones
{
	// PUBLIC

	InputSystem::InputSystem()
	{
		glfwSetInputMode(GL::window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glfwSetCursorPosCallback(GL::window, OnMouse);
	}

	Signature InputSystem::CreateSignature()
	{
		Signature s = 0;
		return s;
	}

	void InputSystem::EntityDestroyed(Entity entity)
	{

	}

	void InputSystem::Update(float dt)
	{
		for (int i = 0; i < inputCount; i++)
		{
			inputs[i].ProcessInput();
		}

		int cursorInputMode = glfwGetInputMode(GL::window, GLFW_CURSOR);

		if (input_escape->wasPressedThisFrame && cursorInputMode != GLFW_CURSOR_NORMAL)
		{
			glfwSetInputMode(GL::window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			changedCursorInputMode = true;
		}

		if (input_leftClick->wasPressedThisFrame && cursorInputMode != GLFW_CURSOR_DISABLED)
		{
			glfwSetInputMode(GL::window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			changedCursorInputMode = true;
		}
	}

	void InputSystem::EndFrame()
	{
		mouseAxis = glm::vec2(0.0f, 0.0f);
	}

	Input* InputSystem::GetInput(Key key)
	{
		for (int i = 0; i < inputCount; i++)
		{
			if (inputs[i].device == InputDevice::Keyboard && inputs[i].key == key)
			{
				return &inputs[i];
			}
		}

		inputs[inputCount].SetKey(key);
		return &inputs[inputCount++];
	}

	Input* InputSystem::GetInput(MouseButton mouseButton)
	{
		for (int i = 0; i < inputCount; i++)
		{
			if (inputs[i].device == InputDevice::Mouse && inputs[i].mouseButton == mouseButton)
			{
				return &inputs[i];
			}
		}

		inputs[inputCount].SetMouseButton(mouseButton);
		return &inputs[inputCount++];
	}

	glm::vec2 InputSystem::GetMouseAxis()
	{
		return mouseAxis;
	}

	// PRIVATE

	void InputSystem::OnMouse(GLFWwindow* window, double xpos, double ypos)
	{
		if (!everDetectedMouse)
		{
			everDetectedMouse = true;
			lastMouseX = xpos;
			lastMouseY = ypos;
		}

		if (changedCursorInputMode)
		{
			mouseAxis = glm::vec2(0.0f, 0.0f);
			changedCursorInputMode = false;
		}
		else
		{
			mouseAxis = glm::vec2(xpos - lastMouseX, ypos - lastMouseY);
			mouseAxis *= sensitivity;
		}



		lastMouseX = xpos;
		lastMouseY = ypos;
	}
}