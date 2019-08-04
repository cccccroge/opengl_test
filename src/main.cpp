#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include "shader.h"
#include "error.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include <memory>

int main(void)
{
    GLFWwindow *window;

    /* Initialize the glfw library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
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
    GLuint shaderProgram = CreateShaderProgram(
        "rsc/vertexShader.glsl",
        "rsc/fragmentShader.glsl");
    GLCALL(glUseProgram(shaderProgram));

    GLint loc = glGetUniformLocation(shaderProgram, "u_color");
    GLfloat r = 0.5;
    GLfloat increment = 0.01;

    /* Main loop */
    while (!glfwWindowShouldClose(window))
    {
        // Unbind and re-bind to do test
/*         va->unbind();
        ib->unbind();
        GLCALL(glUseProgram(0));

        va->bind();
        ib->bind();
        GLCALL(glUseProgram(shaderProgram)); */

        /* Render here */
        GLCALL(glClear(GL_COLOR_BUFFER_BIT));
        GLCALL(glUniform4f(loc, r, 0.5, 0.5, 1));
        GLCALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

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

    // clean up objects
    GLCALL(glDeleteProgram(shaderProgram));

    glfwTerminate();
    return 0;
}
