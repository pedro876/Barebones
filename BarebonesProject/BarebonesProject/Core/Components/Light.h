#pragma once

namespace Barebones
{
	enum class LightType
	{
		Directional,
		Point,
		Spot,
		Area,
	};

	struct Light
	{
	public:
		LightType type{ LightType::Point };
		float range{ 5.0 };
		float intensity{ 2.0 };
		float outerConeAngle{ 70.0 };
		float innerConeAngle{ 0.0 };
		glm::vec3 color{ 1.0, 1.0, 1.0 };
	};
}

