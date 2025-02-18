#pragma once

#include <string>
#include "../Asset.h"
#include "../Shader/Shader.h"
#include "../Texture/Texture.h"

namespace Barebones
{
	

	class Material
	{
	public:
		//struct Property
		//{
		//	enum class Type
		//	{
		//		Bool,
		//		Integer,
		//		Float,
		//		Matrix4x4,
		//		Texture,
		//	};
		//	union Value
		//	{
		//		bool boolValue;
		//		int intValue;
		//		float floatValue;
		//		glm::mat4 matrix4x4Value;
		//		std::weak_ptr<Texture> textureValue;

		//		Value(){}
		//		~Value() {}
		//	};

		//	std::string name;
		//	Type type;
		//	Value value;
		//};

		template<typename T>
		struct Property
		{
			std::string name;
			T value;
		};

		

		std::string name;
		std::weak_ptr<Shader> shader;

		std::vector<Property<bool>> properties_bools;
		std::vector<Property<int>> properties_ints;
		std::vector<Property<float>> properties_floats;
		std::vector<Property<glm::mat4>> properties_matrices;
		std::vector<Property<std::weak_ptr<Texture>>> properties_textures;

		void SetPassCall()
		{
			if (auto shader = this->shader.lock())
			{
				for (auto& p : properties_bools) shader->SetBool(p.name, p.value);
				for (auto& p : properties_ints) shader->SetInt(p.name, p.value);
				for (auto& p : properties_floats) shader->SetFloat(p.name, p.value);
				for (auto& p : properties_matrices) shader->SetMat4(p.name, p.value);
				for (auto& p : properties_textures)
				{
					shader->SetInt(p.name, 0);
					if (auto texture = p.value.lock())
					{
						texture->Use(0);
					}
				}
			}
		}

		/*
		What is a material property?
			- A string name
			- A value (maybe a union??)
		*/
	};
}

