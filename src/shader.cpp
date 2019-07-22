#include "shader.h"
#include <string>
#include <iostream>
#include <fstream>
#include "error.h"

GLuint CreateShaderProgram(const char *vsPath, const char *fsPath)
{
    // file to char[]
    std::ifstream in(vsPath);
    std::string contents((std::istreambuf_iterator<char>(in)), 
        std::istreambuf_iterator<char>());
    const char *vertexShader = contents.c_str();

    std::ifstream in2(fsPath);
    std::string contents2((std::istreambuf_iterator<char>(in2)), 
        std::istreambuf_iterator<char>());
    const char *fragmentShader = contents2.c_str();

    // create program and attach shaders
    GLuint program = glCreateProgram();
    GLuint vs = CompileShader(GL_VERTEX_SHADER, &vertexShader);
    GLuint fs = CompileShader(GL_FRAGMENT_SHADER, &fragmentShader);

    if (vs == 0 || fs == 0) {
        GLCALL(glDeleteProgram(program));
        return 0;
    }

    GLCALL(glAttachShader(program, vs));
    GLCALL(glAttachShader(program, fs));
    GLCALL(glLinkProgram(program));
    GLCALL(glValidateProgram(program));
    
    // clear up
    GLCALL(glDetachShader(program, vs));
    GLCALL(glDetachShader(program, fs));
    GLCALL(glDeleteShader(vs));
    GLCALL(glDeleteShader(fs));
    
    return program;
}

GLuint CompileShader(GLuint type, const char **src)
{
    GLuint id = glCreateShader(type);
    GLCALL(glShaderSource(id, 1, src, nullptr));
    GLCALL(glCompileShader(id));

    // error handling
    GLint success;
    GLCALL(glGetShaderiv(id, GL_COMPILE_STATUS, &success));

    if (success) {
        return id;
    }
    else {
        GLint length;
        GLCALL(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        GLchar info[length];
        GLCALL(glGetShaderInfoLog(id, length, nullptr, info));

        std::cout << "Failed to compile shader:" << std::endl;
        std::cout << info << std::endl;
        GLCALL(glDeleteShader(id));

        return 0;
    }
}