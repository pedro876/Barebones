#include "Object.h"

namespace Barebones
{
	Object::Object(const std::string& name)
	{
		SetName(name);
	}

	std::string Object::GetName() const
	{
		return name;
	}

	void Object::SetName(const std::string& modifiedName)
	{
		this->name = modifiedName;
	}
}