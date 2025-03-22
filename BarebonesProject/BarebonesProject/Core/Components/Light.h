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
	};
}

