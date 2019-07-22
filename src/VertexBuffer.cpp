#include "VertexBuffer.h"
#include "error.h"


VertexBuffer::VertexBuffer(const GLfloat *data, const GLuint size)
{
    GLCALL(glGenBuffers(1, &rendererID));
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, rendererID));
    GLCALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
    GLCALL(glDeleteBuffers(1, &rendererID));
}

void VertexBuffer::bind() const
{
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, rendererID));
}

void VertexBuffer::unbind() const
{
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
