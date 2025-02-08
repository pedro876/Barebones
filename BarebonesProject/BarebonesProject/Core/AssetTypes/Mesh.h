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

	class Mesh
	{
	public:
		friend class GL;

		Mesh(Primitive primitive);
		Mesh(unsigned int indexCount, unsigned int vertexCount, std::vector<unsigned int> indices,
			std::vector<glm::vec3> vertices,
			std::vector<glm::vec3> normals);

	private:
		unsigned int vertexCount = 0;
		unsigned int indexCount = 0;
		unsigned int triangleCount = 0;
		std::vector<glm::vec3> vertices;
		std::vector<unsigned int> indices;
		std::vector<glm::vec3> normals;

		unsigned int EBO; //Element buffer object
		unsigned int VBO; //Vertex buffer object
		unsigned int VAO; //Vertex array object

		void GenerateVAO();
	};


}

