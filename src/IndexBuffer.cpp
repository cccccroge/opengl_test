#include "IndexBuffer.h"
#include "error.h"

IndexBuffer::IndexBuffer()
{
    GLCALL(glGenBuffers(1, &rendererID));
}

IndexBuffer::IndexBuffer(const GLuint *data, const GLuint count):
    count(count)
{
    GLCALL(glGenBuffers(1, &rendererID));
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID));
    GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
    GLCALL(glDeleteBuffers(1, &rendererID));
}

void IndexBuffer::bind() const
{
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID));
}

void IndexBuffer::unbind() const
{
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
