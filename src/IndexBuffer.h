#include <GLEW/glew.h>

class IndexBuffer
{
public:
    IndexBuffer(const GLuint *data, const GLuint count);
    ~IndexBuffer();

    void bind() const;
    void unbind() const;

    inline GLuint getCount() { return count; }

private:
    GLuint rendererID;
    GLuint count;
};