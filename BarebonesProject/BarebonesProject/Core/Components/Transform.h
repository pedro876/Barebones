#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Barebones
{
	struct Transform
	{
		glm::vec3 position{ 0.0f, 0.0f, 0.0f };
		glm::vec3 localRotation{ 0.0f, 0.0f, 0.0f };
		glm::vec3 localScale{ 1.0f, 1.0f, 1.0f };
	};
}

