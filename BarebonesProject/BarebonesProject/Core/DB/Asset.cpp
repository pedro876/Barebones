#include "Asset.h"

namespace Barebones
{
	Asset::Asset(const std::string& path) :
		path(path)
	{
		size_t lastBarIndex = path.find_last_of('/');
		if (lastBarIndex == std::string::npos)
		{
			name = path;
		}
		else
		{
			directory = path.substr(0, lastBarIndex);
			name = path.substr(lastBarIndex + 1, path.size());
		}
	}

	std::string Asset::GetName() const { return name; }
	std::string Asset::GetDirectory() const { return directory; }
	std::string Asset::GetPath() const { return path; }
}