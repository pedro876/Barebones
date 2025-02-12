#pragma once

#include <stdexcept>
#include <format>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <vector>

namespace Barebones
{
	enum class Primitive
	{
		/// <summary>
		/// A 1x1 quad in the XY axis that points towards positive Z.
		/// </summary>
		Quad,
	};

	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 normal;
	};

	class Mesh
	{
	public:
		Mesh(Primitive primitive, bool isReadable = false);
		Mesh(const std::string& name, std::vector<unsigned int> indices, std::vector<Vertex> vertices, bool isReadable = false);

		Mesh(const Mesh&) = delete;
		Mesh& operator=(const Mesh&) = delete;

		Mesh(Mesh&&) noexcept;
		Mesh& operator=(Mesh&&) noexcept;

		void Draw() const;

		~Mesh();

	private:
		std::string name;
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		unsigned int indexCount;
		unsigned int vertexCount;

		bool isReadable;
		unsigned int EBO; //Element buffer object
		unsigned int VBO; //Vertex buffer object
		unsigned int VAO; //Vertex array object

		void GenerateVAO();
	};


}

