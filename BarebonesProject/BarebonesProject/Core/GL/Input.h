#pragma once

#include "KeyCode.h"
#include "GL.h"

namespace Barebones
{
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
			keycode = (int)key;
		}

		void SetKey(Key key)
		{
			this->key = key;
			keycode = (int)key;
		}

		void ProcessInput()
		{
			int state = glfwGetKey(GL::window, keycode);
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

		Key key;
		int keycode;
	};
}