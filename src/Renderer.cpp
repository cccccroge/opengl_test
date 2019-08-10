#include "Renderer.h"

Renderer::Renderer()
{

}

Renderer::~Renderer()
{

}

void Renderer::clear()
{
    GLCALL(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::draw(const VertexArray &vao, const IndexBuffer &ibo, const Shader &shader)
{
    vao.select(0);
    ibo.bind();
    shader.bind();
    GLCALL(glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_INT, nullptr));
}
