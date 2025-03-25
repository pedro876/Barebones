#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <iostream>

namespace Barebones
{
	namespace fs = std::filesystem;

	class File
	{
	public:
		static bool Exists(fs::path path);
		static fs::path GetCurrentWorkingDirectory();
		static fs::path AbsoluteToRelativePath(fs::path absolutePath);
		static fs::path MakeRelativeToFileBeRelativeToCWD(fs::path filePath, fs::path relativePath);
		static std::string Read(fs::path path);
		static std::vector<std::string> ReadLines(fs::path path);
		static void Write(fs::path path, const std::string& text);
		static std::vector<std::string> SplitLine(std::string line, char delimiter);
		static std::string TrimLine(std::string line, char character = ' ');

	private:
		static inline fs::path cwd = std::filesystem::current_path();
	};
}

