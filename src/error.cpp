#include "error.h"

void clearError()
{
    while (glGetError() != GL_NO_ERROR)
    {
        // do nothing here
    }
}

bool checkError(std::string functionName, std::string fileName, int line)
{
    GLenum e = glGetError();
    if (e != GL_NO_ERROR)
    {
        std::cout << "***OpenGL error***" << std::endl
                  << "file: " << fileName << std::endl
                  << "[line] " << line << std::endl
                  << "[function] " << functionName << std::endl
                  << "[error code] 0x" << std::hex << e << std::endl;
        return false;
    }

    return true;
}
