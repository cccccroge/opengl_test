#pragma once
#include <GLEW/glew.h>
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include <vector>
#include <tuple>
#include <memory>

class VertexArray
{
public:
    VertexArray();
    ~VertexArray();

    void bind() const;
    void unbind() const;
    void addVertexBuffer(const std::shared_ptr<VertexBuffer> buffer, const int index);
    void addVertexBufferLayout(const VertexBufferLayout &layout, const int index);
    bool select(const int index) const;

private:
    GLuint rendererID;
    std::vector<std::shared_ptr<VertexBuffer>> buffers;
    std::vector<VertexBufferLayout> layouts;
};