#pragma once

#include <stdexcept>
#include <format>
#include <glad/glad.h>

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

	Mesh(Primitive primitive)
	{
		switch (primitive)
		{
		case Primitive::Quad:
			vertexCount = 4;
			triangleCount = 2;
			indices = new unsigned int[]
				{
					0, 3, 1,
					0, 2, 3
				};
			vertices = new float[]
				{
					-0.5f, -0.5f, 0.0f,
					-0.5f, 0.5f, 0.0f,
					0.5f, -0.5f, 0.0f,
					0.5f, 0.5f, 0.0f
				};
			normals = new float[]
				{
					0.0f, 0.0f, 1.0f,
					0.0f, 0.0f, 1.0f,
					0.0f, 0.0f, 1.0f,
					0.0f, 0.0f, 1.0f
				};
			break;
		default:
			vertexCount = 0;
			triangleCount = 0;
			throw std::logic_error("Primitive type {} not implemented");
			break;
		}

		indexCount = triangleCount * 3;

		//VAO GENERATION
		glGenBuffers(1, &EBO);
		glGenBuffers(1, &VBO);
		glGenVertexArrays(1, &VAO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * vertexCount, vertices, GL_STATIC_DRAW);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 3 * triangleCount, indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
	}

	~Mesh()
	{
		delete[] vertices;
		delete[] indices;
		delete[] normals;
	}

private:
	unsigned int vertexCount = 0;
	unsigned int indexCount = 0;
	unsigned int triangleCount = 0;
	float* vertices = nullptr;
	float* normals = nullptr;
	unsigned int* indices = nullptr;

	unsigned int EBO; //Element buffer object
	unsigned int VBO; //Vertex buffer object
	unsigned int VAO; //Vertex array object
};

