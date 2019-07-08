#include "shader.h"

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
        glDeleteProgram(program);
        return 0;
    }

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);
    
    // clear up
    glDetachShader(program, vs);
    glDetachShader(program, fs);
    glDeleteShader(vs);
    glDeleteShader(fs);
    
    return program;
}

GLuint CompileShader(GLuint type, const char **src)
{
    GLuint id = glCreateShader(type);
    glShaderSource(id, 1, src, nullptr);
    glCompileShader(id);

    // error handling
    GLint success;
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);

    if (success) {
        return id;
    }
    else {
        GLint length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        GLchar info[length];
        glGetShaderInfoLog(id, length, nullptr, info);

        std::cout << "Failed to compile shader:" << std::endl;
        std::cout << info << std::endl;
        glDeleteShader(id);

        return 0;
    }
}