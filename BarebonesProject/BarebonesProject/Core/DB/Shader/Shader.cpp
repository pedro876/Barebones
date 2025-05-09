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

        CompileShader(vShaderCode, fShaderCode);
    }

    Shader::Shader(const std::string& name, const std::string& path) :
        Asset(name)
    {

        std::vector<std::string> lines = File::ReadLines(path);

        std::string vShaderCodeStr;
        std::string fShaderCodeStr;
        State state = GLOBAL;

        for (int i = 0, count = lines.size(); i < count; i++)
        {
            std::string& line = lines[i];
            CheckShaderLine(state, line, path, vShaderCodeStr, fShaderCodeStr);
        }

        std::cout << vShaderCodeStr << "\n\n\n";
        std::cout << fShaderCodeStr << "\n\n\n";

        const char* vShaderCode = vShaderCodeStr.c_str();
        const char* fShaderCode = fShaderCodeStr.c_str();
        CompileShader(vShaderCode, fShaderCode);

        //Assign texture units
        Use();
        GLint numUniforms = 0;
        glGetProgramiv(ID, GL_ACTIVE_UNIFORMS, &numUniforms);
        int textureUnit = 0;
        for (GLint i = 0; i < numUniforms; ++i)
        {
            char name[256];  // Buffer to store the name
            GLsizei length;  // Actual length of the name
            GLint size;      // Size of the uniform (for arrays)
            GLenum type;     // Type of the uniform

            glGetActiveUniform(ID, i, sizeof(name), &length, &size, &type, name);

            // Check if it's a texture sampler
            if (type == GL_SAMPLER_2D || type == GL_SAMPLER_3D || type == GL_SAMPLER_CUBE ||
                type == GL_SAMPLER_2D_SHADOW || type == GL_SAMPLER_2D_ARRAY ||
                type == GL_INT_SAMPLER_2D || type == GL_UNSIGNED_INT_SAMPLER_2D)
            {
                std::string strName = name;
                SetInt(strName, textureUnit);
                textureUnits[strName] = textureUnit++;
            }
        }
    }

    Shader::~Shader()
    {
        glDeleteProgram(ID);
    }
    

    void Shader::Use()
    {
        glUseProgram(ID);
    }


    void Shader::CheckShaderLine(State& state, std::string& line, 
        const std::string& currentPath, std::string& vShaderCodeStr, std::string& fShaderCodeStr)
    {
        if (line.starts_with('#'))
        {
            if (line == "#Global") state = GLOBAL;
            else if (line == "#MaterialProperties") state = MATERIAL_PROPERTIES;
            else if (line == "#Attributes") state = ATTRIBUTES;
            else if (line == "#Varyings") state = VARYINGS;
            else if (line == "#Outputs") state = OUTPUTS;
            else if (line == "#Vertex") state = VERTEX;
            else if (line == "#Fragment") state = FRAGMENT;
            else if (line.starts_with("#include"))
            {
                const int includeHeaderLength = 8;
                const int totalHeaderLength = includeHeaderLength + 2;
                // Remove '#include "' and the final '"'

                std::string includePath = line.substr(totalHeaderLength, line.size() - totalHeaderLength - 1);
                if (includePath.find('/') == std::string::npos)
                {
                    includePath = (std::filesystem::path(currentPath).parent_path() / includePath).string();
                }
                if (File::Exists(includePath))
                {
                    State prevState = state;
                    std::vector<std::string> text = File::ReadLines(includePath);
                    for (int i = 0, count = text.size(); i < count; i++)
                    {
                        std::string& otherLine = text[i];
                        CheckShaderLine(state, otherLine, includePath, vShaderCodeStr, fShaderCodeStr);
                    }
                    state = prevState;
                }
                else
                {
                    std::cerr << "Shader named " << this->name << " couldn't include file with path " << path << "\n";
                }
            }
            else
            {
                vShaderCodeStr += line;
                vShaderCodeStr += "\n";
                fShaderCodeStr += line;
                fShaderCodeStr += "\n";
            }
        }
        else
        {
            switch (state)
            {
            case GLOBAL:
                vShaderCodeStr += line;
                fShaderCodeStr += line;
                vShaderCodeStr += "\n";
                fShaderCodeStr += "\n";
                break;
            case MATERIAL_PROPERTIES:
            {
                defaultProperties.AddSerializedPropertyGLSL(line);
                vShaderCodeStr += line;
                fShaderCodeStr += line;
                vShaderCodeStr += "\n";
                fShaderCodeStr += "\n";
            }
            break;
            case ATTRIBUTES:
            case VERTEX:
                vShaderCodeStr += line;
                vShaderCodeStr += "\n";
                break;
            case VARYINGS:
                if (line.size())
                {
                    vShaderCodeStr += "out ";
                    vShaderCodeStr += line;
                    vShaderCodeStr += "\n";
                    fShaderCodeStr += "in ";
                    fShaderCodeStr += line;
                    fShaderCodeStr += "\n";
                }
                break;
            case OUTPUTS:
            case FRAGMENT:
                fShaderCodeStr += line;
                fShaderCodeStr += "\n";
                break;
            }
        }
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

    void Shader::SetPropertyBlock(const PropertyBlock& block) const
    {
        for (auto& p : block.floats) SetFloat(p.name, p.value);
        for (auto& p : block.ints) SetInt(p.name, p.value);
        for (auto& p : block.bools) SetBool(p.name, p.value);
        for (auto& p : block.vec2s) SetVec2(p.name, p.value);
        for (auto& p : block.vec3s) SetVec3(p.name, p.value);
        for (auto& p : block.vec4s) SetVec4(p.name, p.value);
        for (auto& p : block.ivec2s) SetIVec2(p.name, p.value);
        for (auto& p : block.ivec3s) SetIVec3(p.name, p.value);
        for (auto& p : block.ivec4s) SetIVec4(p.name, p.value);
        for (auto& p : block.bvec2s) SetBVec2(p.name, p.value);
        for (auto& p : block.bvec3s) SetBVec3(p.name, p.value);
        for (auto& p : block.bvec4s) SetBVec4(p.name, p.value);
        for (auto& p : block.textures)
        {
            if (auto texture = p.value.lock())
            {
                auto it = textureUnits.find(p.name);
                if (it != textureUnits.end())
                {
                    int unit = it->second;
                    texture->Use(unit);
                }
                else
                {
                    std::cerr << "Shader " << name << " does not have a texture named " << p.name << "\n";
                }
            }
        }
    }

    void Shader::CompileShader(const char* vShaderCode, const char* fShaderCode)
    {
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