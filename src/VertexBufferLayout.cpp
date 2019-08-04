#include "VertexBufferLayout.h"
#include "utils.h"
#include <vector>
#include <tuple>
#include "error.h"

VertexBufferElement::VertexBufferElement(GLuint count, GLuint type) : 
    count(count), type(type), normalized(false)
{
    switch (type)
    {
    case GL_FLOAT:
    case GL_DOUBLE:
        break;

    case GL_INT:
    case GL_UNSIGNED_INT:
    case GL_BYTE:
    case GL_UNSIGNED_BYTE:
        normalized = true;
        break;

    default:
        break;
    }
}

VertexBufferElement::VertexBufferElement() : 
    count(0), type(GL_FLOAT), normalized(false)
{

}

VertexBufferElement::~VertexBufferElement()
{
}

VertexBufferLayout::VertexBufferLayout() : stride(0)
{
}

VertexBufferLayout::~VertexBufferLayout()
{

}

void VertexBufferLayout::pushElement(const VertexBufferElement &vbe)
{
    // Total size of this element
    GLuint bytes = vbe.count * sizeOfGLType(vbe.type);

    // Push to last offset location
    elements.push_back(std::tuple<VertexBufferElement, GLuint>(vbe, stride));
    stride += bytes;
}

void VertexBufferLayout::setup() const
{
    std::vector< std::tuple<VertexBufferElement, GLuint> >::const_iterator it;
    for (it = elements.begin(); it != elements.end(); ++it) {
        const std::tuple<VertexBufferElement, GLuint> &tup = (*it);
        const VertexBufferElement &element = std::get<0>(tup);
        GLuint offset = std::get<1>(tup);

        GLuint index = it - elements.begin();
        GLint components = element.count;
        GLenum type = element.type;
        GLboolean normalized = element.normalized;
        GLvoid *pointer = (GLvoid *)offset;
        GLCALL(glVertexAttribPointer(index, components, type, normalized, stride, pointer));
        GLCALL(glEnableVertexAttribArray(index));
    }
}
