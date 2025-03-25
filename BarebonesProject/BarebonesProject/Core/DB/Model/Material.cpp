#include "Material.h"

namespace Barebones
{
	void Material::SetPassCall()
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
}