#pragma once

#include <string>
#include "../ECS/Coordinator.h"
#include "DB.h"
#include "../File/File.h"

namespace Barebones
{
	class Asset
	{
	public:
		std::string GetName() const;
		std::string GetDirectory() const;
		std::string GetPath() const;
	protected:
		Asset(const std::string& path);

		Asset(const Asset&) = delete;
		Asset& operator=(const Asset&) = delete;
		Asset(Asset&&) = delete;
		Asset& operator=(Asset&&) = delete;
		std::string path;
		std::string directory;
		std::string name;
	};
}

