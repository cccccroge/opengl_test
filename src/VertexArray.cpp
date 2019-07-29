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

void VertexArray::bind()
{
    GLCALL(glBindVertexArray(rendererID));
}

void VertexArray::unbind()
{
    GLCALL(glBindVertexArray(0));
}

void VertexArray::addVertexBuffer(const VertexBuffer &buffer, int index)
{
    std::tuple<VertexBuffer&, VertexBufferLayout&> tup = 
        std::forward_as_tuple(VertexBuffer(), VertexBufferLayout());

    try
    {
        tup = buffers.at(index);
    }
    catch (std::out_of_range &e)
    {
        // std::cout << e.what() << std::endl;

        // Insert new tuple
        std::get<0>(tup) = buffer;
        buffers.insert(buffers.begin() + index, tup);
    }
    
    // Override existing tuple
    std::get<0>(tup) = buffer;
}

void VertexArray::addVertexBufferLayout(const VertexBufferLayout &layout, int index)
{
    std::tuple<VertexBuffer&, VertexBufferLayout&> tup = 
        std::forward_as_tuple(VertexBuffer(), VertexBufferLayout());

    try
    {
        tup = buffers.at(index);
    }
    catch (std::out_of_range &e)
    {
        // std::cout << e.what() << std::endl;

        // Insert new tuple
        std::get<1>(tup) = layout;
        buffers.insert(buffers.begin() + index, tup);
        return;
    }
    
    // Override existing tuple
    std::get<1>(tup) = layout;
}

bool VertexArray::select(int index)
{
    std::tuple<VertexBuffer&, VertexBufferLayout&> tup = 
        std::forward_as_tuple(VertexBuffer(), VertexBufferLayout());

    try
    {
        tup = buffers.at(index);
    }
    catch (std::out_of_range &e)
    {
        // No buffer here
        std::cout << e.what() << std::endl;
        return false;
    }

    // Bind buffer and setup layout
    VertexBuffer &buffer = std::get<0>(tup);
    VertexBufferLayout &layout = std::get<1>(tup);
    buffer.bind();
    layout.setup();
    
    return true;
}
