#include "Texture.h"

namespace Barebones
{
	Texture::Texture(std::string path) : Asset(path)
	{

	}

	void Texture::Load()
	{
		bool isDefaultTexture = path.starts_with("DefaultTexture");

		if (!File::Exists(path) && !isDefaultTexture)
		{
			std::cerr << "Error: File not found at " << path << "\n";
		}

		glGenTextures(1, &ID);
		glBindTexture(GL_TEXTURE_2D, ID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		unsigned char* data;
		if (isDefaultTexture)
		{
			data = new unsigned char[3];
			if (path.ends_with("White")) { data[0] = 0xFF; data[1] = 0xFF; data[2] = 0xFF; }
			if (path.ends_with("Black")) { data[0] = 0x00; data[1] = 0x00; data[2] = 0x00; }
			if (path.ends_with("Grey")) { data[0] = 0x80; data[1] = 0x80; data[2] = 0x80; }
			if (path.ends_with("Normal")) { data[0] = 0x00; data[1] = 0x00; data[2] = 0xFF; }
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			delete[] data;
		}
		else
		{
			data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

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

		
	}

	void Texture::Use(int textureUnit)
	{
		glActiveTexture(GL_TEXTURE0 + textureUnit);
		glBindTexture(GL_TEXTURE_2D, ID);
	}
}