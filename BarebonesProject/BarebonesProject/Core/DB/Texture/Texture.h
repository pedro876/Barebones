#pragma once
#include "../Asset.h"
#include "../../_External/stb_image.h"
#include <glad/glad.h>

namespace Barebones
{
	class Texture : public Asset
	{
	public:
		Texture(std::string path);
		void Load();
		void Use(int textureUnit);
	private:
		int width = 0;
		int height = 0;
		int nrChannels = 0;
		unsigned int ID = 0;
	};
}