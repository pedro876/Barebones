#include "Input.h"

namespace Barebones
{
	// PRIVATE

	Input::Input()
	{
		key = Key::Undefined;
		index = (int)key;
	}

	void Input::SetKey(Key key)
	{
		this->key = key;
		index = (int)key;
		device = InputDevice::Keyboard;
	}

	void Input::SetMouseButton(MouseButton mouseButton)
	{
		this->mouseButton = mouseButton;
		index = (int)mouseButton;
		device = InputDevice::Mouse;
	}

	void Input::ProcessInput()
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
}