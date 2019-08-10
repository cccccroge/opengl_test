#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

class Renderer
{
public:
    Renderer();
    ~Renderer();

    void clear();
    void draw(const VertexArray &vao, const IndexBuffer &ibo, const Shader &shader);
};