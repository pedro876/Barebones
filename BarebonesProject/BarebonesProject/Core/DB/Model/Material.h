#pragma once

#include <string>
#include "../Asset.h"
#include "../Shader/Shader.h"
#include "../Texture/Texture.h"

namespace Barebones
{
	class Material
	{
	public:
		std::weak_ptr<Shader> shader;
		std::weak_ptr<Texture> baseMap;
		std::string name;
	};
}

