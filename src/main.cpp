#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include "Shader.h"
#include "error.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include <memory>
#include "utils.h"
#include "Renderer.h"

int main(void)
{
    GLFWwindow *window;

    /* Initialize the glfw library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    // glfwSwapInterval(1);

    /* Use GLEW to get GL extensions */
    if (glewInit() != GLEW_OK)
        std::cout << "failed to initialize GLEW" << std::endl;

    /* Show version of OpenGL */
    std::cout << glGetString(GL_VERSION) << std::endl;

    /* Data declaration */
    // Create vertex array
    auto va = std::make_unique<VertexArray>();
    va->bind();

    // Create vertex buffer and its layout working along with the vertex array
    GLfloat points[8] = {
         0.5, -0.5,
         0.5,  0.5,
        -0.5,  0.5,
        -0.5, -0.5};
    auto vb = std::make_shared<VertexBuffer>(points, 8 * sizeof(GLfloat));
    va->addVertexBuffer(vb, 0);
    vb->bind();

    auto vbl = std::make_unique<VertexBufferLayout>();
    vbl->pushElement(VertexBufferElement(2, GL_FLOAT));
    va->addVertexBufferLayout(*vbl, 0);

    va->select(0);

    // Create index buffer
    GLuint indexes[6] = {
        0, 1, 3,
        3, 2, 1};
    auto ib = std::make_unique<IndexBuffer>(indexes, 6);
    ib->bind();

    // Create shaders;
    auto shader = std::make_unique<Shader>();
    shader->addShader(GL_VERTEX_SHADER, "rsc/vertexShader.glsl");
    shader->addShader(GL_FRAGMENT_SHADER, "rsc/fragmentShader.glsl");
    shader->compileProgram();
    shader->bind();

    // Create renderer
    Renderer renderer;

    // Manipulate uniform
    GLfloat r = 0.5;
    GLfloat increment = 0.01;

    /* Main loop */
    while (!glfwWindowShouldClose(window))
    {
        // Unbind and re-bind to do test
        va->unbind();
        ib->unbind();
        shader->unbind();

        va->bind();
        ib->bind();
        shader->bind();

        /* Render here */
        renderer.clear();
        shader->setUniformSingle<4, GLfloat>("u_color", {r, 0.5, 0.5, 1});
        renderer.draw(*va, *ib, *shader);

        /* Changing uniform's value */
        if (r >= 1.0 || r <= 0.0)
        {
            increment = -increment;
        }
        r += increment;

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
