#pragma once

#include "Component.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Serialization.h"

namespace Barebones
{
	class Transform : public Component
	{
	public:
		
	protected:
		std::string ToString() const override;
	private:
		glm::vec3 localPosition = glm::vec3(0.0f);
		glm::vec3 localScale = glm::vec3(1.0f, 1.0f, 1.0f);
		glm::vec3 localRotation = glm::vec3(0.0f);

	public:
		constexpr static auto properties = std::make_tuple(
			SerializeField(&Transform::localPosition, "localPosition"),
			SerializeField(&Transform::localScale, "localScale"),
			SerializeField(&Transform::localRotation, "localRotation")
		);
	};
}

