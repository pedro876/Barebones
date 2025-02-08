#include "Mesh.h"

namespace Barebones
{
	Mesh::Mesh(Primitive primitive)
	{
		switch (primitive)
		{
		case Primitive::Quad:
			vertexCount = 4;
			triangleCount = 2;
			indices = 
				{
					0, 3, 1,
					0, 2, 3
				};
			vertices = 
				{
					glm::vec3(-0.5f, -0.5f, 0.0f),
					glm::vec3(-0.5f, 0.5f, 0.0f),
					glm::vec3(0.5f, -0.5f, 0.0f),
					glm::vec3(0.5f, 0.5f, 0.0f)
				};
			normals = 
				{
					glm::vec3(0.0f, 0.0f, 1.0f),
					glm::vec3(0.0f, 0.0f, 1.0f),
					glm::vec3(0.0f, 0.0f, 1.0f),
					glm::vec3(0.0f, 0.0f, 1.0f)
				};
			break;
		default:
			vertexCount = 0;
			triangleCount = 0;
			throw std::logic_error("Primitive type {} not implemented");
			break;
		}

		indexCount = triangleCount * 3;
		GenerateVAO();
	}

	Mesh::Mesh(unsigned int indexCount, unsigned int vertexCount, std::vector<unsigned int> indices, 
		std::vector<glm::vec3> vertices,
		std::vector<glm::vec3> normals)
		: indexCount(indexCount), vertexCount(vertexCount), indices(indices), 
		vertices(vertices),
		normals(normals)
	{
		triangleCount = indexCount / 3;
		GenerateVAO();
	}

	void Mesh::GenerateVAO()
	{
		//GENERATE BUFFERS
		glGenBuffers(1, &EBO);
		glGenBuffers(1, &VBO);
		glGenVertexArrays(1, &VAO);

		//BIND BUFFERS
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

		//FILL BUFFERS
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 3 * triangleCount, indices.data(), GL_STATIC_DRAW);

		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * 3 * vertexCount, vertices.data(), GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
		glEnableVertexAttribArray(0);
	}

}

