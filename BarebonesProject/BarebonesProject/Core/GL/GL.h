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
#include "../Components/Camera.h"
#include "../Components/Light.h"
#include "UniformBufferObject.h"

namespace Barebones
{
	class GL
	{
	public:
		friend class LightingSystem;
		

		GL();
		~GL();

		bool WindowShouldClose();
		void BeginFrame();
		void EndFrame();

		void SetupCameraProperties(const glm::mat4& viewProjMat);
		
		void DrawMeshRenderer(Transform& transform, const MeshRenderer& renderer);

	private:
		GLFWwindow* window;
		UniformBufferObject uboMatrices;
		UniformBufferObject uboLights;

		const unsigned int MAX_LIGHT_COUNT = 64;
		const unsigned long long UBO_OFFSET_AMBIENT_LIGHT = 0;
		const unsigned long long UBO_OFFSET_DIRECTIONAL_LIGHT_COLOR = UBO_OFFSET_AMBIENT_LIGHT + sizeof(glm::vec4);
		const unsigned long long UBO_OFFSET_DIRECTIONAL_LIGHT_DIR = UBO_OFFSET_DIRECTIONAL_LIGHT_COLOR + sizeof(glm::vec4);
		const unsigned long long UBO_OFFSET_LIGHT_COUNT = UBO_OFFSET_DIRECTIONAL_LIGHT_DIR + sizeof(glm::vec4);
		const unsigned long long UBO_OFFSET_POSITIONS = UBO_OFFSET_LIGHT_COUNT + sizeof(int) * 4;
		const unsigned long long UBO_OFFSET_COLORS = UBO_OFFSET_POSITIONS + sizeof(glm::vec4) * MAX_LIGHT_COUNT;
		const unsigned long long UBO_OFFSET_DIRECTIONS = UBO_OFFSET_COLORS + sizeof(glm::vec4) * MAX_LIGHT_COUNT;
		const unsigned long long UBO_OFFSET_PROPERTIES = UBO_OFFSET_DIRECTIONS + sizeof(glm::vec4) * MAX_LIGHT_COUNT;
		void BeginLightSetup();
		void SetAmbientLight(const glm::vec3& ambientLight);
		void SetDirectionalLight(const Transform* transform, const Light* light);
		void SetAdditionalLightCount(unsigned int lightCount);
		void SetAdditionalLight(unsigned int index, const Transform& transform, const Light& light);
		void EndLightSetup();
		
		
	};
}

