#pragma once

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "../File/File.h"
#include "glm/glm.hpp"
#include <glm/gtc/type_ptr.hpp>

namespace Barebones
{
    class Shader
    {
    public:
        unsigned int ID;

        Shader(const std::string& vertexPath, const std::string& fragmentPath);
        
        void Use();
        void SetBool(const std::string& name, bool value) const;
        void SetInt(const std::string& name, int value) const;
        void SetFloat(const std::string& name, float value) const;
        void SetMat4(const std::string& name, glm::mat4 matrix) const;

    private:
        void CheckCompileErrors(unsigned int shader, std::string type);
    };
}

