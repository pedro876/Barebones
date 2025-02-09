#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#include "../ECS/ECS_Types.h"

namespace Barebones
{
	class TransformSystem;

	struct Transform
	{
	public:
		friend class TransformSystem;
		glm::mat4 GetLocalToWorldMatrix()
		{
			if (dirty)
			{
				localToWorld = glm::mat4(1.0f); // Start with identity matrix
				localToWorld = glm::translate(localToWorld, localPosition);
				localToWorld = localToWorld * glm::toMat4(localRotation);
				localToWorld = glm::scale(localToWorld, localScale);
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
		void SetLocalRotation(glm::vec3 localRotation) { this->localRotation = glm::quat{ glm::radians(localRotation) }; dirty = true; }
		void SetLocalRotation(glm::quat localRotation) { this->localRotation = localRotation; dirty = true; }
		void SetLocalScale(glm::vec3 localScale) { this->localScale = localScale; dirty = true; }

	private:
		glm::vec3 localPosition { 0.0f, 0.0f, 0.0f };
		glm::quat localRotation {1.0f, 0.0f, 0.0f, 0.0f };
		glm::vec3 localScale { 1.0f, 1.0f, 1.0f };

		glm::mat4 localToWorld { 1.0f };
		
		bool dirty{ false };
		EntityCount children { 0 };
		Entity first{ 0 };
		Entity next{ 0 };
		Entity prev{ 0 };
	};
}

