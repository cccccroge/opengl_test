#include "VertexArray.h"
#include "error.h"
#include <exception>
#include <iostream>

VertexArray::VertexArray()
{
    GLCALL(glGenVertexArrays(1, &rendererID));
}

VertexArray::~VertexArray()
{
    GLCALL(glDeleteVertexArrays(1, &rendererID));
}

void VertexArray::bind() const
{
    GLCALL(glBindVertexArray(rendererID));
}

void VertexArray::unbind() const
{
    GLCALL(glBindVertexArray(0));
}

void VertexArray::addVertexBuffer(const std::shared_ptr<VertexBuffer> buffer, const int index)
{    
    try
    {
        buffers.at(index);
    }
    catch (std::out_of_range &e)
    {
        // std::cout << e.what() << std::endl;
        // Insert buffer
        buffers.insert(buffers.begin() + index, buffer);
        return;
    }
    
    // Override existing buffer
    buffers.at(index) = buffer;
}

void VertexArray::addVertexBufferLayout(const VertexBufferLayout &layout, const int index)
{
    try
    {
        layouts.at(index);
    }
    catch (std::out_of_range &e)
    {
        // std::cout << e.what() << std::endl;
        // Insert layout
        layouts.insert(layouts.begin() + index, layout);
        return;
    }
    
    // Override existing layout
    layouts.at(index) = layout;
}

bool VertexArray::select(const int index) const
{
    try
    {
        buffers.at(index);
        layouts.at(index);
    }
    catch (std::out_of_range &e)
    {
        // No buffer here
        return false;
    }

    // Check the buffer has both valid VertexBuffer and VertexBufferLayout
    auto buffer = buffers.at(index);
    auto layout = layouts.at(index);
    if (buffer->getRendererID() == 0)
        return false;
    else if (layout.getStride() == 0)
        return false;

    // Bind buffer and setup layout
    this->bind();
    buffer->bind();
    layout.setup();
    
    return true;
}
