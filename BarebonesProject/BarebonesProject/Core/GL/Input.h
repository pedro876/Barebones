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
		Input();
		void SetKey(Key key);
		void SetMouseButton(MouseButton mouseButton);
		void ProcessInput();

		InputDevice device;
		Key key;
		MouseButton mouseButton;
		int index;
	};
}