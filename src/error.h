#include <GLEW/glew.h>
#include <iostream>

#define ASSERT(x) \
    if (!x)       \
    __builtin_trap()
#define GLCALL(func) \
    clearError();    \
    func;            \
    ASSERT(checkError(#func, __FILE__, __LINE__))

void clearError();
bool checkError(std::string, std::string, int);
