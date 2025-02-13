#pragma once

#include <string>
#include <fstream>
#include <sstream>

namespace Barebones
{
	class File
	{
	public:
		static std::string Read(const std::string& path);
		static void Write(const std::string& path, const std::string& text);
	};
}

