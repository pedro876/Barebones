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

	Mesh(Primitive primitive);
	~Mesh();

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

