#include <GLEW/glew.h>

class VertexBuffer
{
public:
    VertexBuffer(const GLfloat *data, const GLuint size);
    ~VertexBuffer();

    void bind() const;
    void unbind() const;


private:
    GLuint rendererID;
};