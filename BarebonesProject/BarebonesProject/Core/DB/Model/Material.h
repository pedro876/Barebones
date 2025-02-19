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
		template<typename T>
		struct Property
		{
			std::string name;
			T value;

			Property(std::string name, T value) : name(name), value(value) {}
		};

		

		std::string name;
		std::weak_ptr<Shader> shader;

		std::vector<Property<std::string>> properties_string;
		std::vector<Property<float>> properties_float;
		std::vector<Property<int>> properties_int;
		std::vector<Property<bool>> properties_bools;
		std::vector<Property<glm::vec2>> properties_vec2;
		std::vector<Property<glm::vec3>> properties_vec3;
		std::vector<Property<glm::vec4>> properties_vec4;
		std::vector<Property<glm::ivec2>> properties_ivec2;
		std::vector<Property<glm::ivec3>> properties_ivec3;
		std::vector<Property<glm::ivec4>> properties_ivec4;
		std::vector<Property<glm::bvec2>> properties_bvec2;
		std::vector<Property<glm::bvec3>> properties_bvec3; 
		std::vector<Property<glm::bvec4>> properties_bvec4;
		std::vector<Property<std::weak_ptr<Texture>>> properties_texture;

		void SetPassCall()
		{
			if (auto shader = this->shader.lock())
			{
				for (auto& p : properties_float) shader->SetFloat(p.name, p.value);
				for (auto& p : properties_int) shader->SetInt(p.name, p.value);
				for (auto& p : properties_bools) shader->SetBool(p.name, p.value);
				for (auto& p : properties_texture)
				{
					shader->SetInt(p.name, 0);
					if (auto texture = p.value.lock())
					{
						texture->Use(0);
					}
				}
			}
		}
	};
}

