#pragma once

#include <format>

namespace Barebones
{
	template <typename Class, typename T>
	struct SerializeField
	{
		constexpr SerializeField(T Class::* aMember, const char* aName) :
			member{ aMember }, name{ aName }
		{

		}

		T Class::*member;
		const char* name;
	};

	//template<typename Class, typename T>
	//constexpr auto property(T Class::* member, const char* name)
	//{
	//	return PropertyImpl<Class, T>{member, name};
	//}

	//std::string SerializeProperty(int variable)
	//{
	//	return std::to_string(variable);
	//}

	//std::string SerializeProperty(glm::vec3 variable)
	//{
	//	return std::format("({}, {}, {})", variable.x, variable.y, variable.z);
	//}
}