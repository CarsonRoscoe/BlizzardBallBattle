#pragma once

#include <map>
#include "Shader.h"
#include <string>

class ShaderFactory {
private:
    map<std::string, *Shader> shaders;
    ~ShaderFactory();
    
public:
    *Shader GetShader(std::string fragmentShaderFile, std::string vertexShaderFile);
}