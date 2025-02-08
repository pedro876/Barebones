#pragma once

#include <string>

namespace Barebones
{
	class Asset
	{
	public:
		std::string GetName() const;
	protected:
		Asset();
		Asset(const std::string& name);

		Asset(const Asset&) = delete;
		Asset& operator=(const Asset&) = delete;
		Asset(Asset&&) = delete;
		Asset& operator=(Asset&&) = delete;
		std::string name;
	};
}

