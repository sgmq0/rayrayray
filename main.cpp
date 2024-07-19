// Test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

float vertices[] = {

     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
};

unsigned int indices[] = {
    0, 1, 2
};

int main()
{

    //initialize GLFW
    glfwInit();

    // configure GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // explicitly tell GLFW to use the core-profile
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // create a window object to hold all windowing data
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // pass GLAD the function that loads the OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // tell openGL the size of the rendering window
    glViewport(0, 0, 800, 600);

    // when a user resizes the window, the viewport should also be adjusted
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // setup shaders with the shader class
    const char* vertexPath = "vertex.glsl";
    const char* fragmentPath = "fragment.glsl";
    Shader shader = Shader(vertexPath, fragmentPath);

    // create VAO and VBO objects and generate buffer ID
    unsigned int VBO, VAO, EBO;
    glGenBuffers(1, &EBO);

    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    // 1. bind vertex array object
    glBindVertexArray(VAO);

    // 2. copy our vertices array in a buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 3. set our vertex attribute pointers
    // position:
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color:
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // also do the same with the elements
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // to continuously draw the window, create a render loop:
    while (!glfwWindowShouldClose(window)) {

        // input
        processInput(window);

        // rendering commands go here
        glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        float timeValue = glfwGetTime();
        float greenValue = (sin(timeValue) / 2.0f) + 0.5f;

        // 4. draw the object
        shader.use();

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

        // check and call events, and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // deallocate all resources
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    // terminate GLFW
    glfwTerminate();
}