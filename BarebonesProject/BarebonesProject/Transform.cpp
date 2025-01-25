#include "Transform.h"
#include <format>

std::string Transform::ToString() const
{
	return std::format("{}_{}_{}", this->localPosition.x, this->localPosition.y, this->localPosition.z);
}
