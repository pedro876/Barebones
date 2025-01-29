//#pragma once
//
//#include <format>
//
//namespace Barebones
//{
//	template <typename Class, typename T>
//	struct SerializeField
//	{
//		constexpr SerializeField(T Class::* aMember, const char* aName) :
//			member{ aMember }, name{ aName }
//		{
//
//		}
//
//		T Class::*member;
//		const char* name;
//	};
//}