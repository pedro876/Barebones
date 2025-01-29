#include "File.h"
#include <iostream>

namespace Barebones
{
	std::string File::Read(const std::string& path)
	{
		std::string content;

		try
		{
			std::ifstream file;
			file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
			file.open(path);
			std::stringstream stream;
			stream << file.rdbuf();
			content = stream.str();
		}
		catch (const std::exception& e)
		{
			//TODO: control what happens when a file cannot be succesfully read
		}

		std::cout << content << std::endl;

		return content;
	}

	void File::Write(const std::string& path, const std::string& text)
	{
		try
		{
			std::ofstream file;
			file.exceptions(std::ofstream::failbit | std::ofstream::badbit);
			file.open(path);
			file << text;
		}
		catch (const std::exception& e)
		{
			//TODO: control what happens when a file cannot be succesfully read
		}
	}

}

