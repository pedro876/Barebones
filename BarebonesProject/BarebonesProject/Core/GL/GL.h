#pragma once

#include <iostream>
#include <fstream>
#include <filesystem>
#include <cassert>
#include <stdexcept>
#include <memory>

// OPEN GLAND THIRD PARTY INCLUDES:
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../_External/stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// BAREBONES
#include "../DB/Shader/Shader.h"
#include "../DB/Model/Mesh.h"
#include "../Components/Transform.h"
#include "../Components/MeshRenderer.h"

namespace Barebones
{
	class GL
	{
	public:
		GL();
		~GL();

		bool WindowShouldClose();
		void BeginFrame();
		void EndFrame();

		void DrawMeshRenderer(const glm::mat4& viewProjMat, Transform& transform, const MeshRenderer& renderer);

	private:
		GLFWwindow* window;
	};
}

