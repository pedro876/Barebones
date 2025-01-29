#pragma once

#include <string>

namespace Barebones
{
	class Object
	{
	public:
		Object(const std::string& name);
		std::string GetName() const;
		void SetName(const std::string& modifiedName);
	private:
		std::string name;
	};
}

