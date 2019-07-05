#include "shader.h"

GLuint CreateShaderProgram(const char **vertexShader, const char **fragmentShader)
{
    GLuint program = glCreateProgram();
    GLuint vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    GLuint fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    if (vs == 0 || fs == 0) {
        glDeleteProgram(program);
        return 0;
    }

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);
    
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