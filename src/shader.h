#pragma once
#include <GLEW/glew.h>


GLuint CreateShaderProgram(const char *vertexShader, const char *fragmentShader);
GLuint CompileShader(GLuint type, const char ** src);