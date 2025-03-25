#include "File.h"
#include <iostream>

namespace Barebones
{
	bool File::Exists(fs::path path) { return fs::exists(path); }
	fs::path File::GetCurrentWorkingDirectory() { return cwd; }
	fs::path File::AbsoluteToRelativePath(fs::path absolutePath) { return fs::relative(absolutePath); }

	fs::path File::MakeRelativeToFileBeRelativeToCWD(fs::path filePath, fs::path relativePath)
	{
		fs::path absoluteBasePath = fs::canonical(filePath);
		fs::path absoluteTargetPath = absoluteBasePath.parent_path() / relativePath;
		fs::path relativeToCWD = fs::relative(absoluteTargetPath, cwd);
		return relativeToCWD;
	}

	std::string File::Read(fs::path path)
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

		//std::cout << content << std::endl;

		return content;
	}

	std::vector<std::string> File::ReadLines(fs::path path)
	{
		std::vector<std::string> lines;

		try
		{
			std::ifstream file;
			file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
			file.open(path);
			std::string line;
			while (std::getline(file, line))
			{
				lines.push_back(line);
			}
		}
		catch (const std::exception& e)
		{
			//TODO: control what happens when a file cannot be succesfully read
		}
		return lines;
	}

	void File::Write(fs::path path, const std::string& text)
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

	std::vector<std::string> File::SplitLine(std::string line, char delimiter)
	{
		std::vector<std::string> tokens;
		size_t pos = 0;
		std::string token;
		while ((pos = line.find(delimiter)) != std::string::npos)
		{
			token = line.substr(0, pos);
			tokens.push_back(token);
			line.erase(0, pos + 1); // + 1 to erase the delimiter
		}
		tokens.push_back(line);
		return tokens;
	}

	std::string File::TrimLine(std::string line, char character)
	{
		size_t size = line.size();
		if (!size) return line;

		while (line[0] == character) line = line.substr(1, --size);
		while (line[size-1] == character) line = line.substr(0, --size);

		return line;
	}

}

