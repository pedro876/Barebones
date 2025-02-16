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
		static bool Exists(fs::path path){ return fs::exists(path); }
		static fs::path GetCurrentWorkingDirectory() { return cwd; }
		static fs::path AbsoluteToRelativePath(fs::path absolutePath)
		{
			return fs::relative(absolutePath);
		}
		static fs::path MakeRelativeToFileBeRelativeToCWD(fs::path filePath, fs::path relativePath)
		{
			fs::path absoluteBasePath = fs::canonical(filePath);
			fs::path absoluteTargetPath = absoluteBasePath.parent_path() / relativePath;
			fs::path relativeToCWD = fs::relative(absoluteTargetPath, cwd);
			return relativeToCWD;
		}
		static std::string Read(const std::string& path);
		static void Write(const std::string& path, const std::string& text);

	private:
		static inline fs::path cwd = std::filesystem::current_path();
	};
}

