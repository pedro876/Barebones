#include "UniformBufferObject.h"

namespace Barebones
{
	// PUBLIC

	UniformBufferObject::UniformBufferObject() : ID(0), name("Unitialized"), binding(0), size(0) {}
	UniformBufferObject::~UniformBufferObject()
	{
		glDeleteBuffers(1, &ID);
	}

	void UniformBufferObject::Initialize(std::string name, unsigned int binding, unsigned long long size)
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

	void UniformBufferObject::SetShaderUBO(unsigned int programID)
	{
		unsigned int blockIndex = glGetUniformBlockIndex(programID, name.c_str());
		if (blockIndex != GL_INVALID_INDEX)
		{
			glUniformBlockBinding(programID, blockIndex, binding);
		}
	}

	void UniformBufferObject::Bind()
	{
		glBindBuffer(GL_UNIFORM_BUFFER, ID);
	}

	void UniformBufferObject::SetData(unsigned long long offset, unsigned long long size, const void* ptr)
	{
		glBufferSubData(GL_UNIFORM_BUFFER, offset, size, ptr);
	}

	void UniformBufferObject::Unbind()
	{
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}
}