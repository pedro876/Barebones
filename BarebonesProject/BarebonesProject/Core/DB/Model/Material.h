#pragma once

#include <string>
#include "../Asset.h"
#include "../Shader/Shader.h"

namespace Barebones
{
	class Material
	{
	public:
		std::weak_ptr<Shader> shader;
		std::string name;
	};
}

