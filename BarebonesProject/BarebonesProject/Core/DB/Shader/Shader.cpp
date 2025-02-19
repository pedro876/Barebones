#include "Shader.h"

namespace Barebones
{
    Shader::Shader(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath) :
        Asset(name)
    {
        const std::string vShaderCodeStr = File::Read(vertexPath);
        const std::string fShaderCodeStr = File::Read(fragmentPath);

        const char* vShaderCode = vShaderCodeStr.c_str();
        const char* fShaderCode = fShaderCodeStr.c_str();

        // 2. compile shaders
        unsigned int vertex, fragment;
        // vertex shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        CheckCompileErrors(vertex, "VERTEX");
        // fragment Shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        CheckCompileErrors(fragment, "FRAGMENT");
        // shader Program
        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        glLinkProgram(ID);
        CheckCompileErrors(ID, "PROGRAM");
        // delete the shaders as they're linked into our program now and no longer necessary
        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    //Shader::Shader(Shader&& other) noexcept :
    //    Asset(other.name),
    //    ID(other.ID)
    //{
    //    other.ID = 0;
    //}

    //Shader& Shader::operator=(Shader&& other) noexcept
    //{
    //    if (this != &other)
    //    {
    //        name = other.name;
    //        ID = other.ID;
    //        other.ID = 0;
    //    }

    //    return *this;
    //}

    Shader::~Shader()
    {
        glDeleteProgram(ID);
    }

    void Shader::Use()
    {
        glUseProgram(ID);
    }

    void Shader::SetBool(const std::string& name, bool value) const { glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value); }
    void Shader::SetInt(const std::string& name, int value) const { glUniform1i(glGetUniformLocation(ID, name.c_str()), value); }
    void Shader::SetFloat(const std::string& name, float value) const { glUniform1f(glGetUniformLocation(ID, name.c_str()), value); }

    void Shader::SetVec2(const std::string& name, const glm::vec2& value)   const { glUniform2f(glGetUniformLocation(ID, name.c_str()), value.x, value.y); }
    void Shader::SetVec3(const std::string& name, const glm::vec3& value)   const { glUniform3f(glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z); }
    void Shader::SetVec4(const std::string& name, const glm::vec4& value)   const { glUniform4f(glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z, value.w); }
    void Shader::SetIVec2(const std::string& name, const glm::ivec2& value) const { glUniform2i(glGetUniformLocation(ID, name.c_str()), value.x, value.y); } 
    void Shader::SetIVec3(const std::string& name, const glm::ivec3& value) const { glUniform3i(glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z); } 
    void Shader::SetIVec4(const std::string& name, const glm::ivec4& value) const { glUniform4i(glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z, value.w); } 
    void Shader::SetBVec2(const std::string& name, const glm::bvec2& value) const { glUniform2i(glGetUniformLocation(ID, name.c_str()), value.x, value.y); } 
    void Shader::SetBVec3(const std::string& name, const glm::bvec3& value) const { glUniform3i(glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z); } 
    void Shader::SetBVec4(const std::string& name, const glm::bvec4& value) const { glUniform4i(glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z, value.w); } 

    void Shader::SetMat4(const std::string& name, glm::mat4 matrix) const
    {
        int matrixLoc = glGetUniformLocation(ID, name.c_str());
        glUniformMatrix4fv(matrixLoc, 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void Shader::CheckCompileErrors(unsigned int shader, std::string type)
    {
        int success;
        char infoLog[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
    }
}