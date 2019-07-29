#pragma once
#include <GLEW/glew.h>
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include <vector>
#include <tuple>

class VertexArray
{
public:
    VertexArray();
    ~VertexArray();

    void bind();
    void unbind();
    void addVertexBuffer(const VertexBuffer &buffer, int index);
    void addVertexBufferLayout(const VertexBufferLayout &layout, int index);
    bool select(int index);

private:
    GLuint rendererID;
    std::vector< std::tuple<VertexBuffer&, VertexBufferLayout&> > buffers;
};