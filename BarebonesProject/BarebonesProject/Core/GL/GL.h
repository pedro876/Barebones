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

		static void Init();
		static void End();

		static bool WindowShouldClose();
		static void BeginFrame();
		static void EndFrame();
		static float GetAspectRatio();
		static unsigned int GetScreenWidth();
		static unsigned int GetScreenHeight();

		static void SetupCameraProperties(const glm::mat4& viewProjMat);
		static void DrawMeshRenderer(Transform& transform, const MeshRenderer& renderer);

	private:
		static inline GLFWwindow* window;
		static inline UniformBufferObject uboMatrices;
		static inline UniformBufferObject uboLights;
		static inline unsigned int screenWidth = 1280;
		static inline unsigned int screenHeight = 720;
		
		static void OnWindowResize(GLFWwindow* window, int width, int height);
		
		static const unsigned int MAX_LIGHT_COUNT = 64;
		static const unsigned long long UBO_OFFSET_AMBIENT_LIGHT = 0;
		static const unsigned long long UBO_OFFSET_DIRECTIONAL_LIGHT_COLOR = UBO_OFFSET_AMBIENT_LIGHT + sizeof(glm::vec4);
		static const unsigned long long UBO_OFFSET_DIRECTIONAL_LIGHT_DIR = UBO_OFFSET_DIRECTIONAL_LIGHT_COLOR + sizeof(glm::vec4);
		static const unsigned long long UBO_OFFSET_LIGHT_COUNT = UBO_OFFSET_DIRECTIONAL_LIGHT_DIR + sizeof(glm::vec4);
		static const unsigned long long UBO_OFFSET_POSITIONS = UBO_OFFSET_LIGHT_COUNT + sizeof(int) * 4;
		static const unsigned long long UBO_OFFSET_COLORS = UBO_OFFSET_POSITIONS + sizeof(glm::vec4) * MAX_LIGHT_COUNT;
		static const unsigned long long UBO_OFFSET_DIRECTIONS = UBO_OFFSET_COLORS + sizeof(glm::vec4) * MAX_LIGHT_COUNT;
		static const unsigned long long UBO_OFFSET_PROPERTIES = UBO_OFFSET_DIRECTIONS + sizeof(glm::vec4) * MAX_LIGHT_COUNT;
		static void BeginLightSetup();
		static void SetAmbientLight(const glm::vec3& ambientLight);
		static void SetDirectionalLight(const Transform* transform, const Light* light);
		static void SetAdditionalLightCount(unsigned int lightCount);
		static void SetAdditionalLight(unsigned int index, const Transform& transform, const Light& light);
		static void EndLightSetup();
		
	};
	
}

