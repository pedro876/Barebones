#pragma once

#include <string>
#include "Object.h"
#include "Shader.h"

namespace Barebones
{
	class Material : public Object
	{
	public:
		Shader* shader;

		Material(const std::string& name, Shader* shader) : 
			Object(name) , shader(shader)
		{
			
		}
	};
}

