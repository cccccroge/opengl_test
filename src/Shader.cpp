#include "Shader.h"
#include <iostream>
#include "error.h"
#include "utils.h"
#include <typeinfo>

Shader::Shader() : program(0), vertexShader(ShaderStruct()), fragmentShader(ShaderStruct())
{
    program = glCreateProgram();
    vertexShader.setShaderID(glCreateShader(GL_VERTEX_SHADER));
    fragmentShader.setShaderID(glCreateShader(GL_FRAGMENT_SHADER));
}

Shader::~Shader()
{
    GLCALL(glDeleteShader(vertexShader.getShaderID()));
    GLCALL(glDeleteShader(fragmentShader.getShaderID()));
    GLCALL(glDeleteProgram(program));

}
void Shader::bind() const
{
    GLCALL(glUseProgram(program));
}

void Shader::unbind() const
{
    GLCALL(glUseProgram(0));
}

bool Shader::addShader(const GLuint type, const std::string &path)
{
    // Path to Cstring source code
    const std::string srcString = file2String(path);
    const char *src = srcString.c_str();
    const GLint length = srcString.length();

    // Add the shader code in coresponding type
    GLuint shader = getShaderStruct(type).getShaderID();
    GLCALL(glShaderSource(shader, 1, &src, &length));
    GLCALL(glCompileShader(shader));

    // Shader compile error handling
    return validateShader(type);
}

void Shader::compileProgram()
{
    // Attach valid shaders on program
    std::vector<GLuint> validIDs = getValidShaderIDs();
    for (auto id : validIDs) {
        GLCALL(glAttachShader(program, id));
    }

    // Make program
    GLCALL(glLinkProgram(program));
    GLCALL(glValidateProgram(program));
    
    // Clear up
    for (auto id : validIDs) {
        GLCALL(glDetachShader(program, id));
    }
}

bool Shader::validateShader(const GLuint type)
{
    // Check existence
    GLuint shader = getShaderStruct(type).getShaderID();
    if (shader == 0) {
        getShaderStruct(type).setValid(false);
        return false;
    }

    // Check compile status
    GLint success;
    GLCALL(glGetShaderiv(shader, GL_COMPILE_STATUS, &success));

    if (success) {
        getShaderStruct(type).setValid(true);
        return true;
    }
    else {
        getShaderStruct(type).setValid(false);

        GLint length;
        GLCALL(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length));
        GLchar info[length];
        GLCALL(glGetShaderInfoLog(shader, length, nullptr, info));

        std::cout << "Failed to compile shader:" << std::endl;
        std::cout << info << std::endl;

        return false;
    }
}

ShaderStruct& Shader::getShaderStruct(const GLuint type)
{
    switch (type)
    {
    case GL_VERTEX_SHADER:
        return vertexShader;    
    case GL_FRAGMENT_SHADER:
        return fragmentShader;
    default:
        return vertexShader;
    }
}

std::vector<GLuint> Shader::getValidShaderIDs()
{
    std::vector<GLuint> ids;
    
    if (vertexShader.getValid())
        ids.push_back(vertexShader.getShaderID());
    if (fragmentShader.getValid())
        ids.push_back(fragmentShader.getShaderID());
    
    return ids;
}
