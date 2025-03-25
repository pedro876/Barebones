#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Barebones
{
	enum class Key
	{
		Undefined = -1,
		Escape = GLFW_KEY_ESCAPE,
		Shift = GLFW_KEY_LEFT_SHIFT,
		W = GLFW_KEY_W,
		A = GLFW_KEY_A,
		S = GLFW_KEY_S,
		D = GLFW_KEY_D,
	};

	enum class MouseButton
	{
		LeftClick = GLFW_MOUSE_BUTTON_LEFT
	};
}