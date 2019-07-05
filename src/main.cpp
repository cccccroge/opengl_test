#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include "shader.h"


int main(void)
{
    GLFWwindow* window;

    /* Initialize the glfw library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Use GLEW to get GL extensions */
    if (glewInit() != GLEW_OK)
        std::cout << "failed to initialize GLEW" << std::endl;

    /* Show version of OpenGL */
    std::cout << glGetString(GL_VERSION) << std::endl;

    /* Data declaration */
    // create buffer and select it
    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);

    // specify points of the triangle and put it to buffer
    GLfloat points[6] = {
        -0.5, -0.5,
         0.5, -0.5,
         0.0,  0.5
    };
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), points, GL_STATIC_DRAW);

    // specify the vertex attributes layout
    GLint components = 2;
    GLsizei stride = components * sizeof(float);
    glVertexAttribPointer(0, components, GL_FLOAT, GL_FALSE, stride, 0);
    glEnableVertexAttribArray(0);
    const GLvoid *pointer = (GLvoid*)1;

    // create shaders
    const char *vertexShader = R"(
        #version 130

        in vec4 position;

        void main()
        {
            gl_Position = position;
        }
        )";
    const char *fragmentShader = R"(
        #version 130

        out vec4 color;

        void main()
        {
            color = vec4(1.0, 0.0, 0.0, 1.0);
        }
        )";

    GLuint shaderProgram = CreateShaderProgram(&vertexShader, &fragmentShader);
    glUseProgram(shaderProgram);

    /* Main loop */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        /* Poll for and process events */
        glfwPollEvents();
    }

    // clean up objects
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}