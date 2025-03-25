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

		UniformBufferObject();
		~UniformBufferObject();

		UniformBufferObject(const UniformBufferObject&) = delete;
		UniformBufferObject& operator=(const UniformBufferObject&) = delete;
		UniformBufferObject(UniformBufferObject&&) = delete;
		UniformBufferObject& operator=(UniformBufferObject&&) = delete;

		void Initialize(std::string name, unsigned int binding, unsigned long long size);
		void SetShaderUBO(unsigned int programID);
		void Bind();
		void SetData(unsigned long long offset, unsigned long long size, const void* ptr);
		void Unbind();
	};
}