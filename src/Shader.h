#pragma once
#include <GLEW/glew.h>
#include <string>
#include <vector>
#include <initializer_list>
#include "error.h"

class ShaderStruct
{
public:
    inline ShaderStruct() : shaderID(0), valid(false) {}

    inline GLuint getShaderID() { return shaderID; }
    inline bool getValid() { return valid; }
    inline void setShaderID(const GLuint id) { shaderID = id; }
    inline void setValid(const bool isValid) { valid = isValid; }

private:
    GLuint shaderID;
    bool valid;
};

class Shader
{
public:
    Shader();
    ~Shader();
    void bind() const;
    void unbind() const;
    bool addShader(const GLuint type, const std::string &path);
    void compileProgram();

    template <int size, typename T>
    void setUniformSingle(const GLchar *name, std::initializer_list<T> list)
    {
        GLint loc = glGetUniformLocation(program, name);
        auto first = list.begin();

        if (typeid(T) == typeid(GLfloat)) {
            if (size == 1)
                GLCALL(glUniform1f(loc, *first));
            else if (size == 2)
                GLCALL(glUniform2f(loc, *first, *(first+1)));
            else if (size == 3)
                GLCALL(glUniform3f(loc, *first, *(first+1), *(first+2)));
            else if (size == 4)
                GLCALL(glUniform4f(loc, *first, *(first+1), *(first+2), *(first+3)));
        }
    }
/*     void setUniformArray();
    void setUniformMatrix(); */

private:
    GLuint program;
    ShaderStruct vertexShader;
    ShaderStruct fragmentShader;

private:
    bool validateShader(const GLuint type);
    ShaderStruct& getShaderStruct(const GLuint type);
    std::vector<GLuint> getValidShaderIDs();
};
