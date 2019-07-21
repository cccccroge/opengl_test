#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include "shader.h"
#include "error.h"


int main(void)
{
    GLFWwindow* window;

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
    // create buffer and select it
    GLuint vao;
    GLCALL(glGenVertexArrays(1, &vao));
    GLCALL(glBindVertexArray(vao));
    GLuint vbo;
    GLCALL(glGenBuffers(1, &vbo));
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, vbo));
    GLuint ibo;
    GLCALL(glGenBuffers(1, &ibo));
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));

    // points of the triangles forming a rectangle, and
    // indexes of them to form two triangles
    GLfloat points[8] = {
         0.5, -0.5,
         0.5,  0.5,
        -0.5,  0.5,
        -0.5, -0.5
    };
    GLuint indexes[6] = {
        0, 1, 3,
        3, 2, 1
    };
    GLCALL(glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), points, GL_STATIC_DRAW));
    GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(int), indexes, GL_STATIC_DRAW));

    // specify the vertex attributes layout
    GLint components = 2;
    GLsizei stride = components * sizeof(float);
    GLCALL(glVertexAttribPointer(0, components, GL_FLOAT, GL_FALSE, stride, 0));
    GLCALL(glEnableVertexAttribArray(0));

    // create shaders;
    GLuint shaderProgram = CreateShaderProgram(
        "rsc/vertexShader.glsl", 
        "rsc/fragmentShader.glsl");
    GLCALL(glUseProgram(shaderProgram));

    // Get uniforms
    GLint loc = glGetUniformLocation(shaderProgram, "u_color");
    GLfloat r = 0.5;
    GLfloat increment = 0.01;

    /* Main loop */
    while (!glfwWindowShouldClose(window))
    {
        // Unbind and re-bind to do test
        GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
        GLCALL(glDisableVertexAttribArray(0));
        GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
        GLCALL(glUseProgram(0));
        
        GLCALL(glBindVertexArray(vao));
        GLCALL(glEnableVertexAttribArray(0));
        GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
        GLCALL(glUseProgram(shaderProgram));

        /* Render here */
        GLCALL(glClear(GL_COLOR_BUFFER_BIT));
        GLCALL(glUniform4f(loc, r, 0.5, 0.5, 1));
        GLCALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

        /* Changing uniform's value */
        if (r >= 1.0 || r <= 0.0) {
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
