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

		void AddSerializedPropertyCSV(std::string line)
		{
			ProcessTokens(line, ';');
		}

		void AddSerializedPropertyGLSL(std::string line)
		{
			std::vector<std::string> parts = File::SplitLine(line, '=');
			if (parts.size() <= 1) return;

			std::string name = File::SplitLine(File::TrimLine(parts[0]), ' ').back();

			std::string right = File::TrimLine(parts[1]);
			size_t leftParentheses = right.find_first_of('(');
			std::string type = right.substr(0, leftParentheses);

			if (type == "float") type = "Float";
			else if (type == "int") type = "Integer";
			else if (type == "bool") type = "Boolean";
			else if (type.starts_with("vec")) type = "FloatArray";
			else if (type.starts_with("ivec")) type = "IntegerArray";
			else if (type.starts_with("bvec")) type = "BooleanArray";

			line = std::format("{},{},{}", type, name, right.substr(leftParentheses + 1, right.size() - leftParentheses - 3));
			ProcessTokens(line, ',');
		}

	private:
		void ProcessTokens(std::string line, char delimiter)
		{
			std::vector<std::string> tokens = File::SplitLine(line, delimiter);
			std::string& type = tokens[0];
			std::string& name = tokens[1];
			int vectorSize = tokens.size() - 2;

			if (type == "String") strings.emplace_back(Property<std::string>(name, tokens[2]));
			else if (type == "Float") floats.emplace_back(Property<float>(name, std::stof(tokens[2])));
			else if (type == "Integer") ints.emplace_back(Property<int>(name, std::stoi(tokens[2])));
			else if (type == "Boolean") bools.emplace_back(Property<bool>(name, tokens[2] == "True"));
			else if (type == "FloatArray")
			{
				if (vectorSize == 2) vec2s.emplace_back(name, glm::vec2(std::stof(tokens[2]), std::stof(tokens[3])));
				if (vectorSize == 3) vec3s.emplace_back(name, glm::vec3(std::stof(tokens[2]), std::stof(tokens[3]), std::stof(tokens[4])));
				if (vectorSize == 4) vec4s.emplace_back(name, glm::vec4(std::stof(tokens[2]), std::stof(tokens[3]), std::stof(tokens[4]), std::stof(tokens[5])));
			}
			else if (type == "IntegerArray")
			{
				if (vectorSize == 2) ivec2s.emplace_back(name, glm::ivec2(std::stoi(tokens[2]), std::stoi(tokens[3])));
				if (vectorSize == 3) ivec3s.emplace_back(name, glm::ivec3(std::stoi(tokens[2]), std::stoi(tokens[3]), std::stoi(tokens[4])));
				if (vectorSize == 4) ivec4s.emplace_back(name, glm::ivec4(std::stoi(tokens[2]), std::stoi(tokens[3]), std::stoi(tokens[4]), std::stoi(tokens[5])));
			}
			else if (type == "BooleanArray")
			{
				if (vectorSize == 2) bvec2s.emplace_back(name, glm::bvec2(tokens[2] == "True", tokens[3] == "True"));
				if (vectorSize == 3) bvec3s.emplace_back(name, glm::bvec3(tokens[2] == "True", tokens[3] == "True", tokens[4] == "True"));
				if (vectorSize == 4) bvec4s.emplace_back(name, glm::bvec4(tokens[2] == "True", tokens[3] == "True", tokens[4] == "True", tokens[5] == "True"));
			}
		}
	};
}