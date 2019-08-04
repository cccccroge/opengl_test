#pragma once
#include <GLEW/glew.h>
#include <vector>
#include <tuple>

class VertexBufferElement
{
public:
    friend class VertexBufferLayout;

public:
    VertexBufferElement(GLuint count, GLuint type);
    VertexBufferElement();
    ~VertexBufferElement();

    inline GLuint getCount() { return count; }
    inline GLuint getType() { return type; }
    inline bool getNormalized() { return normalized; }

private:
    GLuint count;
    GLuint type;
    bool normalized;
};

class VertexBufferLayout
{
public:
    VertexBufferLayout();
    ~VertexBufferLayout();

    void pushElement(const VertexBufferElement &vbe);
    void setup() const;

    inline GLuint getStride() const { return stride; }

private:
    // each element is 
    // (element , byte offset to the beginning of that vertex)
    std::vector< std::tuple<VertexBufferElement, GLuint> > elements;
    GLuint stride;
};