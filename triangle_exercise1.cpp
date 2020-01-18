//
// Created by jingwen on 08/01/2020.
// Draw two triangles with different colors using two fragment shaders
// and two VBOs
//

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

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

    /* 2. startup shaders */
    // Vertex Shader
    constexpr const char* shader_vertex =
            R"glsl(
    #version 330 core
    layout (location = 0) in vec3 pos;
    void main()
    {
        gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);
    }
    )glsl";

    // Fragment Shader Orange
    constexpr const char* shader_fragment_orange =
            R"glsl(
    #version 330 core
    out vec4 FragColor;

    void main()
    {
        FragColor =  vec4(1.0f, 0.5f, 0.2f, 1.0f);
    }
    )glsl";

    // Fragment Shader Yellow
    constexpr const char* shader_fragment_yellow =
            R"glsl(
    #version 330 core
    out vec4 FragColor;

    void main()
    {
        FragColor =  vec4(1.0f, 1.0f, 0.0f, 1.0f);
    }
    )glsl";

    // Compile Shaders
    GLuint vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &shader_vertex, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShaderOrange;
    fragmentShaderOrange = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderOrange, 1, &shader_fragment_orange, NULL);
    glCompileShader(fragmentShaderOrange);

    GLuint fragmentShaderYellow;
    fragmentShaderYellow = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderYellow, 1, &shader_fragment_yellow, NULL);
    glCompileShader(fragmentShaderYellow);

    // Link shaders
    GLuint shaderProgramOrange;
    shaderProgramOrange = glCreateProgram();
    glAttachShader(shaderProgramOrange, vertexShader);
    glAttachShader(shaderProgramOrange, fragmentShaderOrange);
    glLinkProgram(shaderProgramOrange);

    GLuint  shaderProgramYellow;
    shaderProgramYellow = glCreateProgram();
    glAttachShader(shaderProgramYellow, vertexShader);
    glAttachShader(shaderProgramYellow, fragmentShaderYellow);
    glLinkProgram(shaderProgramYellow);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShaderOrange);
    glDeleteShader(fragmentShaderYellow);

    // set up vertex data
    GLfloat triangle1[] = {
            // left triangle
            -0.5f, 0.0f, 0.0f,
            -0.5f, 0.4f, 0.0f,
            0.0f,  0.0f, 0.0f
    };

    GLfloat triangle2[] = {
            // right triangle
            0.0f, 0.0f, 0.0f,
            0.0f, 0.5f, 0.0f,
            0.4f, 0.5f, 0.0f
    };

    // vertex buffer object, vertex array object
    GLuint VBO[2], VAO[2];
    glGenBuffers(2, VBO);
    glGenVertexArrays(2, VAO);

    // Bind VAO1
    glBindVertexArray(VAO[0]);
    // Copy data to VBO1 (on GPU)
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]); // bind vbo to target GL_ARRAY_BUFFER
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle1), triangle1, GL_STATIC_DRAW); // transfer data to buffer
    // Set the vertex attribute pointers
    glEnableVertexAttribArray(0); // index = 0
    // index, size, type, normalize, stride, offset
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (void*) 0);

    // Bind VAO2
    glBindVertexArray(VAO[1]);
    // Copy data to VBO2 (on GPU)
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]); // bind vbo to target GL_ARRAY_BUFFER
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle2), triangle2, GL_STATIC_DRAW); // transfer data to buffer
    // Set the vertex attribute pointers
    glEnableVertexAttribArray(0); // index = 0
    // index, size, type, normalize, stride, offset
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (void*) 0);

    /* 3. main loop */
    while (!glfwWindowShouldClose(window))
    {
        // keyboard input
        processInput(window);

        // rednering commands here
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // Each time we call glClear, the entire color buffer will be filled with this color
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgramOrange);
        glBindVertexArray(VAO[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glUseProgram(shaderProgramYellow);
        glBindVertexArray(VAO[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // check and call events and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}