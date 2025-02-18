#pragma once
#include "../Asset.h"
#include "../../_External/stb_image.h"
#include <glad/glad.h>

namespace Barebones
{
	class Texture : public Asset
	{
	public:
		Texture(std::string path) : Asset(path)
		{

		}

		void Load()
		{
			if (!File::Exists(path))
			{
				std::cerr << "Error: File not found at " << path << "\n";
			}

			glGenTextures(1, &ID);
			glBindTexture(GL_TEXTURE_2D, ID);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
			if (data)
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
				glGenerateMipmap(GL_TEXTURE_2D);
			}
			else
			{
				const char* failureReason = stbi_failure_reason();
				std::cout << "Failed to load image: " << failureReason << "\n";
			}
			
			stbi_image_free(data);
		}

		void Use(int textureUnit)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, ID);
		}
	private:
		int width = 0;
		int height = 0;
		int nrChannels = 0;
		unsigned int ID = 0;
	};
}