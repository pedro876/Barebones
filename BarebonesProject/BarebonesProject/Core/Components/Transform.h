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

		// GETTERS
		glm::vec3 GetLocalPosition() const { return localPosition; }
		glm::quat GetLocalRotation() const { return localRotation; }
		glm::vec3 GetLocalScale() const { return localScale; }

		glm::mat4 GetDirtyLocalToWorldMatrix() const { return localToWorld; }
		glm::vec3 GetDirtyRight() const { return glm::vec3(localToWorld[0]); };
		glm::vec3 GetDirtyUp() const { return glm::vec3(localToWorld[1]); };
		glm::vec3 GetDirtyForward() const { return glm::vec3(localToWorld[2]); };
		glm::vec3 GetDirtyWorldPosition() const { return glm::vec3(localToWorld[3]); }

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
		unsigned int children { 0 };
		Entity firstChild{ 0 };
		Entity nextSibling{ 0 };
		Entity prevSibling{ 0 };
		Entity parent{ 0 };

		glm::mat4 GetLocalToParentMatrix() const
		{
			glm::mat4 matrix{ 1.0f };
			matrix = glm::translate(matrix, localPosition);
			matrix = matrix * glm::toMat4(localRotation);
			matrix = glm::scale(matrix, localScale);
			return matrix;
		}
	};
}

