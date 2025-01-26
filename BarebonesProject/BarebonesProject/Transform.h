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
		glm::vec3 localPosition;
		glm::vec3 localScale;
		glm::vec3 localRotation;

	public:
		constexpr static auto properties = std::make_tuple(
			SerializeField(&Transform::localPosition, "localPosition"),
			SerializeField(&Transform::localScale, "localScale"),
			SerializeField(&Transform::localRotation, "localRotation")
		);
	};
}

