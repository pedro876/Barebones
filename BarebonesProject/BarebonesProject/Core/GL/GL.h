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
		const unsigned int MAX_LIGHT_COUNT = 64;
		

		GL();
		~GL();

		bool WindowShouldClose();
		void BeginFrame();
		void EndFrame();

		void SetupCameraProperties(const glm::mat4& viewProjMat);
		void SetAmbientLight(const glm::vec3& ambientLight);
		void SetDirectionalLight(const Transform* transform, const Light* light);
		void SetAdditionalLightCount(unsigned int lightCount);
		void SetAdditionalLight(unsigned int index, const Transform& transform, const Light& light);
		void DrawMeshRenderer(Transform& transform, const MeshRenderer& renderer);

	private:
		const unsigned long long ambientLightOffset = 0;
		const unsigned long long directionalLightColorOffset = ambientLightOffset + sizeof(glm::vec4);
		const unsigned long long directionalLightDirOffset = directionalLightColorOffset + sizeof(glm::vec4);
		const unsigned long long lightCountOffset = directionalLightDirOffset + sizeof(glm::vec4);
		const unsigned long long positionsOffset = lightCountOffset + sizeof(int) * 4;
		const unsigned long long colorsOffset = positionsOffset + sizeof(glm::vec4) * MAX_LIGHT_COUNT;
		const unsigned long long directionsOffset = colorsOffset + sizeof(glm::vec4) * MAX_LIGHT_COUNT;
		const unsigned long long propertiesOffset = directionsOffset + sizeof(glm::vec4) * MAX_LIGHT_COUNT;
		GLFWwindow* window;
		UniformBufferObject uboMatrices;
		UniformBufferObject uboLights;
	};
}

