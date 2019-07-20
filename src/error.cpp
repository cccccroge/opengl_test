#include "error.h"


void clearError()
{
    while (glGetError() != GL_NO_ERROR) {
        // do nothing here
    }
}

void checkError(std::string functionName, std::string fileName, int line)
{
    GLenum e = glGetError();
    if (e != GL_NO_ERROR) {
        std::cout << "***OpenGL error***" << std::endl\
            << "file: " << fileName << std::endl\
            << "[error code] " << e << std::endl\
            << "[function] " << functionName << std::endl\
            << "[line] " << line << std::endl;
        __builtin_trap();
    }
}
