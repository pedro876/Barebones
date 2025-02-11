#pragma once

#include <string>
#include "../Asset.h"
#include "../Shader/Shader.h"

namespace Barebones
{
	class Material : public Asset
	{
	public:
		std::weak_ptr<Shader> shader;

		Material(const std::string& name, std::weak_ptr<Shader> shader) :
			Asset(name) , shader(shader)
		{
			
		}
	};
}

