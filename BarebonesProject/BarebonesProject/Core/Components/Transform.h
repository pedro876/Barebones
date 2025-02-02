#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

namespace Barebones
{
	struct Transform
	{
	public:

		glm::mat4 GetLocalToWorldMatrix()
		{
			if (dirty)
			{
				localToWorld = glm::scale(glm::mat4{ 1.0f }, localScale);
				localToWorld = glm::toMat4(localRotation) * localToWorld;
				localToWorld = glm::translate(localToWorld, localPosition);
				dirty = false;
			}
			return localToWorld;
		}

		// GETTERS
		glm::vec3 GetLocalPosition() const { return localPosition; }
		glm::quat GetLocalRotation() const { return localRotation; }
		glm::vec3 GetLocalScale() const { return localScale; }

		// SETTERS
		void SetLocalPosition(glm::vec3 localPosition) { this->localPosition = localPosition; dirty = true; }
		void SetLocalRotation(glm::vec3 localRotation) { this->localRotation = localRotation; dirty = true; }
		void SetLocalScale(glm::vec3 localScale) { this->localScale = localScale; dirty = true; }

	private:
		glm::vec3 localPosition { 0.0f, 0.0f, 0.0f };
		glm::quat localRotation {1.0f, 0.0f, 0.0f, 0.0f };
		glm::vec3 localScale { 1.0f, 1.0f, 1.0f };

		glm::mat4 localToWorld { 1.0f };
		bool dirty{ false };
	};
}

