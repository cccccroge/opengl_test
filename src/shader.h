#include <GLEW/glew.h>
#include <string>
#include <iostream>


GLuint CreateShaderProgram(const char **vertexShader, const char **fragmentShader);
GLuint CompileShader(GLuint type, const char ** src);