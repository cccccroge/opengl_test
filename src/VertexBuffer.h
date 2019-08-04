#pragma once
#include <GLEW/glew.h>

class VertexBuffer
{
public:
    VertexBuffer();
    VertexBuffer(const GLfloat *data, const GLuint size);
    VertexBuffer(const VertexBuffer &vb);
    VertexBuffer& operator=(const VertexBuffer &vb) = default;
    VertexBuffer(VertexBuffer &&vb) = default;
    ~VertexBuffer();

    void bind() const;
    void unbind() const;

    inline GLuint getRendererID() const { return rendererID; }

private:
    GLuint rendererID;
};