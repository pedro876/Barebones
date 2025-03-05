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
		std::string name;
		std::weak_ptr<Shader> shader;
		PropertyBlock properties;
		

		void SetPassCall()
		{
			// The shader should have the vectors too for all its default properties.
			// When setting the pass call, we should iterate all the shader default properties.
			// If the material has it, use it, otherwise set the default value.

			if (auto shader = this->shader.lock())
			{
				shader->SetPropertyBlock(shader->defaultProperties);
				shader->SetPropertyBlock(properties);
			}
		}
	};
}

