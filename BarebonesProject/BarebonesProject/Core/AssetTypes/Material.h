#pragma once

#include <string>
#include "Asset.h"
#include "Shader.h"

namespace Barebones
{
	class Material : public Asset
	{
	public:
		Shader* shader;

		Material(const std::string& name, Shader* shader) : 
			Asset(name) , shader(shader)
		{
			
		}
	};
}

