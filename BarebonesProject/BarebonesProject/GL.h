#pragma once

#include <iostream>
#include <fstream>
#include <filesystem>
#include <cassert>
#include <stdexcept>

// OPEN GLAND THIRD PARTY INCLUDES:
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class GL
{
public:
	GL();
	~GL();

	bool WindowShouldClose();
	void BeginFrame();
	void EndFrame();

private:
	GLFWwindow* window;
};