#include <GLEW/glew.h>
#include <string>
#include <iostream>
#include <fstream>


GLuint CreateShaderProgram(const char *vertexShader, const char *fragmentShader);
GLuint CompileShader(GLuint type, const char ** src);