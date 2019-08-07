#include "utils.h"
#include <fstream>

GLuint sizeOfGLType(GLuint type)
{
    switch (type)
    {
    case GL_UNSIGNED_INT:
        return sizeof(GLuint);
        break;
    case GL_FLOAT:
        return sizeof(GLfloat);
        break;
    case GL_DOUBLE:
        return sizeof(GLdouble);
        break;
    case GL_UNSIGNED_BYTE:
        return sizeof(GLubyte);
        break;
    default:
        return 4; 
    }
}

const std::string file2String(const std::string &path)
{
    std::ifstream in(path);
    std::string contents((std::istreambuf_iterator<char>(in)), 
        std::istreambuf_iterator<char>());

    return contents;
}