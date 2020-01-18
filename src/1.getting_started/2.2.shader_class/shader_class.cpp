//
// Created by jingwen on 18/01/2020.
//

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <learnopengl/shader.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    // if pressed the ESCAPE key, otherwise return GLFW_RELEASE
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main()
{
    /* 1. setting up environment */
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to load GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Initialize GLAD, manages function pointers for OpenGL
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    Shader ourShader("shader.vs", "shader.fs");

    // set up vertex data
    GLfloat vertices[] = {
            // positions        // colors
            -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
            0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
    };

    // vertex buffer object
    // vertex array object
    GLuint VBO, VAO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    // Bind VAO
    glBindVertexArray(VAO);
    // Copy data to VBO (on GPU)
    glBindBuffer(GL_ARRAY_BUFFER, VBO); // bind vbo to target GL_ARRAY_BUFFER
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // transfer data to buffer

    // Set the vertex attribute pointers
    glEnableVertexAttribArray(0); // index = 0
    // index, size, type, normalize, stride, offset
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (GLvoid*) 0);
    // Set the vertex attribute pointers
    glEnableVertexAttribArray(1); // index = 1
    // index, size, type, normalize, stride, offset
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (GLvoid*) (3 * sizeof(GLfloat)));

    /* 3. main loop */
    while (!glfwWindowShouldClose(window))
    {
        // keyboard input
        processInput(window);

        // rednering commands here
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // Each time we call glClear, the entire color buffer will be filled with this color
        glClear(GL_COLOR_BUFFER_BIT);

        ourShader.use();

        // update the horizontal offset
        float timeValue = glfwGetTime();
        float offset = sin(timeValue) / 3.0f;
        ourShader.setFloat("h_offset", offset);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // check and call events and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

