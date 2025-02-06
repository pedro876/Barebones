#pragma once

#include <stdexcept>
#include <format>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>

namespace Barebones
{
	enum class Primitive
	{
		/// <summary>
		/// A 1x1 quad in the XY axis that points towards positive Z.
		/// </summary>
		Model,
		Quad,
	};

	class Mesh
	{
	public:
		friend class GL;

		Mesh(Primitive primitive);
		Mesh(unsigned int vertexCount, unsigned int indexCount, glm::vec3* vertices, unsigned int* indices, 
			glm::vec3* normals = nullptr);
		~Mesh();

	private:
		unsigned int vertexCount = 0;
		unsigned int indexCount = 0;
		unsigned int triangleCount = 0;
		glm::vec3* vertices = nullptr;
		unsigned int* indices = nullptr;
		glm::vec3* normals = nullptr;

		unsigned int EBO; //Element buffer object
		unsigned int VBO; //Vertex buffer object
		unsigned int VAO; //Vertex array object

		void GenerateVAO();
	};


}

