#pragma once

#include "glm/glm.hpp"

namespace Barebones
{
	struct Camera
	{
	public:
		float fieldOfView{ 60.0f };
		float near{ 0.1f };
		float far{ 1000.0f };
		bool orthographic{ false };
		unsigned int priority{ 0 };

		glm::mat4 GetProjectionMatrix(float aspect)
		{
			return glm::perspective(glm::radians(fieldOfView), aspect, near, far);
		}
	};
}

