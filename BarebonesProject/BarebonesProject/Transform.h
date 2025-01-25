#pragma once

#include "Component.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Transform : public Component
{
protected:
	std::string ToString() const override;
private:
	glm::vec3 localPosition;
	glm::vec3 localScale;
	glm::vec3 localRotation;
};