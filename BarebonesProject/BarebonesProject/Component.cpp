#include "Component.h"

namespace Barebones
{
	std::string Component::ToString() const
	{
		return "";
	}

	std::ostream& operator<<(std::ostream& os, const Component& component)
	{
		std::string content = component.ToString();
		std::string typeName = typeid(component).name();

		const std::string classPrefix = "class ";
		if (typeName.starts_with(classPrefix))
		{
			typeName = typeName.substr(classPrefix.length());
		}

		os << typeName;
		if (!content.empty())
		{
			os << "_" << content;
		}
		return os;
	}

	std::ostream& operator<<(std::ostream& os, const Component* component)
	{
		if (component == nullptr)
		{
			os << "Null component pointer";
		}
		else
		{
			os << *component;
		}

		return os;
	}



}

