#include "Transform.h"
#include <format>

namespace Barebones
{
	std::string Transform::ToString() const
	{
		return std::format("{}_{}_{}", this->localPosition.x, this->localPosition.y, this->localPosition.z);
	}

}

