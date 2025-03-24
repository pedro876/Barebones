#pragma once

#include "KeyCode.h"
#include "GL.h"

namespace Barebones
{
	enum class InputDevice
	{
		Keyboard,
		Mouse,
	};

	class Input
	{
	public:
		friend class InputSystem;
		
		Input(const Input&) = delete;
		Input& operator=(const Input&) = delete;
		Input(Input&&) = delete;
		Input& operator=(Input&&) = delete;

		bool isPressed = false;
		bool wasPressedThisFrame = false;
		bool wasReleasedThisFrame = false;

	private:
		Input()
		{
			key = Key::Undefined;
			index = (int)key;
		}

		void SetKey(Key key)
		{
			this->key = key;
			index = (int)key;
			device = InputDevice::Keyboard;
		}

		void SetMouseButton(MouseButton mouseButton)
		{
			this->mouseButton = mouseButton;
			index = (int)mouseButton;
			device = InputDevice::Mouse;
		}

		void ProcessInput()
		{
			int state;
			switch (device)
			{
			default:
			case InputDevice::Keyboard: state = glfwGetKey(GL::window, index); break;
			case InputDevice::Mouse: state = glfwGetMouseButton(GL::window, index); break;
			}


			wasPressedThisFrame = false;
			wasReleasedThisFrame = false;
			if (state == GLFW_PRESS)
			{
				if (!isPressed) wasPressedThisFrame = true;
				isPressed = true;
			}
			else
			{
				if (isPressed) wasReleasedThisFrame = true;
				isPressed = false;
			}
		}

		InputDevice device;
		Key key;
		MouseButton mouseButton;
		int index;
	};
}