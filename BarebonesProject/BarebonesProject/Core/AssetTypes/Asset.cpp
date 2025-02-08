#include "Asset.h"

namespace Barebones
{
	Asset::Asset() : name("Unknown name") {}

	Asset::Asset(const std::string& name) : name(name) {}

	std::string Asset::GetName() const { return name; }
}