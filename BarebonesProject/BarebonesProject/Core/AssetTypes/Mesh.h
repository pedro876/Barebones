#pragma once

#include <stdexcept>
#include <format>
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
		Mesh(unsigned int vertexCount, unsigned int indexCount, float* vertices, unsigned int* indices, 
			float* normals = nullptr);
		~Mesh();

	private:
		unsigned int vertexCount = 0;
		unsigned int indexCount = 0;
		unsigned int triangleCount = 0;
		float* vertices = nullptr;
		unsigned int* indices = nullptr;
		float* normals = nullptr;

		unsigned int EBO; //Element buffer object
		unsigned int VBO; //Vertex buffer object
		unsigned int VAO; //Vertex array object

		void GenerateVAO();
	};


}

