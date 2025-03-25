#pragma once

#include <vector>
#include <string>
#include "../Texture/Texture.h"
#include <glm/glm.hpp>
#include "../../File/File.h"
#include <format>

namespace Barebones
{
	template<typename T>
	struct Property
	{
		std::string name;
		T value;

		Property(std::string name, T value) : name(name), value(value) {}
	};

	struct PropertyBlock
	{
	public:
		std::vector<Property<std::string>> strings;
		std::vector<Property<float>> floats;
		std::vector<Property<int>> ints;
		std::vector<Property<bool>> bools;
		std::vector<Property<glm::vec2>> vec2s;
		std::vector<Property<glm::vec3>> vec3s;
		std::vector<Property<glm::vec4>> vec4s;
		std::vector<Property<glm::ivec2>> ivec2s;
		std::vector<Property<glm::ivec3>> ivec3s;
		std::vector<Property<glm::ivec4>> ivec4s;
		std::vector<Property<glm::bvec2>> bvec2s;
		std::vector<Property<glm::bvec3>> bvec3s;
		std::vector<Property<glm::bvec4>> bvec4s;
		std::vector<Property<std::weak_ptr<Texture>>> textures;

		void AddSerializedPropertyCSV(std::string line);
		void AddSerializedPropertyGLSL(std::string line);

	private:
		void ProcessTokens(std::string line, char delimiter);
	};
}