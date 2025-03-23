#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>

namespace Barebones
{
	class UniformBufferObject
	{
	public:
		unsigned int ID;
		std::string name;
		unsigned int binding;
		unsigned long long size;

		UniformBufferObject() : ID(0), name("Unitialized"), binding(0), size(0) {}

		UniformBufferObject(const UniformBufferObject&) = delete;
		UniformBufferObject& operator=(const UniformBufferObject&) = delete;
		UniformBufferObject(UniformBufferObject&&) = delete;
		UniformBufferObject& operator=(UniformBufferObject&&) = delete;

		void Initialize(std::string name, unsigned int binding, unsigned long long size)
		{
			this->name = name;
			this->binding = binding;
			this->size = size;
			glGenBuffers(1, &ID);
			glBindBuffer(GL_UNIFORM_BUFFER, ID);
			glBufferData(GL_UNIFORM_BUFFER, size, NULL, GL_STATIC_DRAW);
			glBindBuffer(GL_UNIFORM_BUFFER, 0);
			glBindBufferBase(GL_UNIFORM_BUFFER, binding, ID);
		}

		~UniformBufferObject()
		{
			glDeleteBuffers(1, &ID);
		}

		void SetShaderUBO(unsigned int programID)
		{
			unsigned int blockIndex = glGetUniformBlockIndex(programID, name.c_str());
			if (blockIndex != GL_INVALID_INDEX)
			{
				glUniformBlockBinding(programID, blockIndex, binding);
			}
		}

		void Bind()
		{
			glBindBuffer(GL_UNIFORM_BUFFER, ID);
		}

		void SetData(unsigned long long offset, unsigned long long size, const void* ptr)
		{
			glBufferSubData(GL_UNIFORM_BUFFER, offset, size, ptr);
		}

		void Unbind()
		{
			glBindBuffer(GL_UNIFORM_BUFFER, 0);
		}
	};
}