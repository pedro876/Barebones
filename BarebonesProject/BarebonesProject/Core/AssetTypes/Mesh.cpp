#include "Mesh.h"

namespace Barebones
{
	Mesh::Mesh(Primitive primitive, bool isReadable) : Asset("Unknown"), isReadable(isReadable)
	{
		switch (primitive)
		{
		case Primitive::Quad:
			this->name = "M_Quad";
			indices = 
				{
					0, 3, 1,
					0, 2, 3
				};
			vertices = 
				{
					Vertex(glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)),
					Vertex(glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)),
					Vertex(glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)),
					Vertex(glm::vec3(0.5f, 0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f))
				};
			break;
		default:
			throw std::logic_error("Primitive type not implemented");
			break;
		}

		GenerateVAO();
	}

	Mesh::Mesh(const std::string& name, std::vector<unsigned int> indices, std::vector<Vertex> vertices, bool isReadable)
		: Asset(name), indices(indices), vertices(vertices), isReadable(isReadable)
	{
		GenerateVAO();
	}

	Mesh::Mesh(Mesh&& other) noexcept :
		Asset(other.name),
		indices(std::move(other.indices)),
		vertices(std::move(other.vertices)),
		indexCount(other.indexCount),
		vertexCount(other.vertexCount),
		isReadable(other.isReadable),
		EBO(other.EBO),
		VBO(other.VBO),
		VAO(other.VAO)
	{
		other.VAO = other.VBO = other.EBO = 0;
		other.indexCount = other.vertexCount = 0;
		other.isReadable = true;
	}

	Mesh& Mesh::operator=(Mesh&& other) noexcept
	{
		if (this != &other)
		{
			name = other.name;
			indices = std::move(other.indices);
			vertices = std::move(other.vertices);
			indexCount = other.indexCount;
			vertexCount = other.vertexCount;
			isReadable = other.isReadable;
			VAO = other.VAO;
			VBO = other.VBO;
			EBO = other.EBO;

			other.VAO = other.VBO = other.EBO = 0;
			other.indexCount = other.vertexCount = 0;
			other.isReadable = false;
		}

		return *this;
	}

	Mesh::~Mesh()
	{
		//Won't do anything if the buffers == 0
		glDeleteBuffers(1, &VAO);
		glDeleteBuffers(1, &EBO);
		glDeleteBuffers(1, &VBO);
	}

	void Mesh::Draw() const
	{
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
	}

	void Mesh::GenerateVAO()
	{
		indexCount = indices.size();
		vertexCount = vertices.size();

		//GENERATE BUFFERS
		glGenBuffers(1, &EBO);
		glGenBuffers(1, &VBO);
		glGenVertexArrays(1, &VAO);

		//BIND BUFFERS
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

		//FILL INDICES
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indexCount, indices.data(), GL_STATIC_DRAW);

		//FILL ATTRIBUTES
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertexCount, vertices.data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
		
		glBindVertexArray(0);

		//If mesh data won't be accessed in CPU anymore, release it.
		if (!isReadable)
		{
			indices.clear();
			indices.shrink_to_fit();
			vertices.clear();
			vertices.shrink_to_fit();
		}
	}

}

