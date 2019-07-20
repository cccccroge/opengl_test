#include <GLEW/glew.h>
#include <iostream>


#define ASSERT(func) clearError();\
    func;\
    checkError(#func, __FILE__, __LINE__)

void clearError();
void checkError(std::string, std::string, int);
