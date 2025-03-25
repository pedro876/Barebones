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
		

		void SetPassCall();
	};
}

