#pragma once

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "../../File/File.h"
#include "glm/glm.hpp"
#include <glm/gtc/type_ptr.hpp>
#include "../Asset.h"
#include "PropertyBlock.h"
#include <unordered_map>

namespace Barebones
{
    class GL;
    class Shader : public Asset
    {
    public:
        friend class GL;
        unsigned int ID;
        PropertyBlock defaultProperties;

        Shader(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath);
        Shader(const std::string& name, const std::string& path);

        //Shader(const Shader&) = delete;
        //Shader& operator=(const Shader&) = delete;

        //Shader(Shader&&) noexcept;
        //Shader& operator=(Shader&&) noexcept;

        ~Shader();

        void Use();
        void SetFloat(const std::string& name, float value) const;
        void SetInt(const std::string& name, int value) const;
        void SetBool(const std::string& name, bool value) const;
        void SetVec2(const std::string& name, const glm::vec2& value) const;
        void SetVec3(const std::string& name, const glm::vec3& value) const;
        void SetVec4(const std::string& name, const glm::vec4& value) const;
        void SetIVec2(const std::string& name, const glm::ivec2& value) const;
        void SetIVec3(const std::string& name, const glm::ivec3& value) const;
        void SetIVec4(const std::string& name, const glm::ivec4& value) const;
        void SetBVec2(const std::string& name, const glm::bvec2& value) const;
        void SetBVec3(const std::string& name, const glm::bvec3& value) const;
        void SetBVec4(const std::string& name, const glm::bvec4& value) const;

        void SetMat4(const std::string& name, glm::mat4 matrix) const;


        void SetPropertyBlock(const PropertyBlock& block) const;
    private:
        bool setUBOs = false;
        std::unordered_map<std::string, int> textureUnits;

        enum State
        {
            GLOBAL,
            MATERIAL_PROPERTIES,
            ATTRIBUTES,
            VARYINGS,
            OUTPUTS,
            VERTEX,
            FRAGMENT,
        };

        void CompileShader(const char* vShaderCode, const char* fShaderCode);
        void CheckShaderLine(State& state, const std::string& line, 
            const std::string& currentPath, std::string& vShaderCodeStr, std::string& fShaderCodeStr);
        void CheckCompileErrors(unsigned int shader, std::string type);
    };
}

