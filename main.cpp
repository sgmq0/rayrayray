// Test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

float vertices1[] = {
    -0.5, 0.5, 0.0,
    -0.5, -0.5, 0.0,
    0.3, 0.5, 0.0,
};

float vertices2[] = {
    -0.3, -0.5, 0.0,
    0.5, -0.5, 0.0,
    0.5, 0.5, 0.0
};

unsigned int indices[] = {
    0, 1, 2,
};

char* readFileToCharArray(const std::string& filePath) {
    // Open the file
    std::ifstream file(filePath, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filePath << std::endl;
        return nullptr;
    }

    // Get the size of the file
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    // Read the file into a string
    std::vector<char> buffer(size);
    if (file.read(buffer.data(), size)) {
        // Allocate memory for the char* array
        char* shaderCode = new char[size + 1];
        std::copy(buffer.begin(), buffer.end(), shaderCode);
        shaderCode[size] = '\0'; // Null-terminate the string

        return shaderCode;
    }
    else {
        std::cerr << "Failed to read file: " << filePath << std::endl;
        return nullptr;
    }
}

int main()
{
    const char* vertexShaderSource = readFileToCharArray("vertex.glsl");
    const char* fragmentShaderSource1 = readFileToCharArray("fragment.glsl");
    const char* fragmentShaderSource2 = readFileToCharArray("fragment.glsl");

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

    // create a shader object
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // do the same for our fragment shader
    unsigned int fragmentShader1 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader1, 1, &fragmentShaderSource1, NULL);
    glCompileShader(fragmentShader1);

    unsigned int fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, NULL);
    glCompileShader(fragmentShader2);

    // create a shader program that will be linked with our shaders
    unsigned int shaderProgram1 = glCreateProgram();
    unsigned int shaderProgram2 = glCreateProgram();

    // attach compiled shaders to the shader program object and link them
    glAttachShader(shaderProgram1, vertexShader);
    glAttachShader(shaderProgram1, fragmentShader1);
    glLinkProgram(shaderProgram1);

    glAttachShader(shaderProgram2, vertexShader);
    glAttachShader(shaderProgram2, fragmentShader2);
    glLinkProgram(shaderProgram2);

    // delete the shader objects once they're inside the shader program
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader1);
    glDeleteShader(fragmentShader2);

    // create VAO and VBO objects and generate buffer ID
    unsigned int VBO1, VAO1, VBO2, VAO2, EBO;
    glGenBuffers(1, &EBO);

    glGenBuffers(1, &VBO1);
    glGenVertexArrays(1, &VAO1);
    glGenBuffers(1, &VBO2);
    glGenVertexArrays(1, &VAO2);

    // 1. bind vertex array object
    glBindVertexArray(VAO1);

    // 2. copy our vertices array in a buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);

    // 3. set our vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // also do the same with the elements
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBindVertexArray(VAO2);

    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

    // 3. set our vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

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
        float greenValue1 = (sin(timeValue) / 2.0f) + 0.5f;
        float greenValue2 = (sin(timeValue + 3.14) / 2.0f) + 0.5f;
        int vertexColorLocation1 = glGetUniformLocation(shaderProgram1, "ourColor");
        int vertexColorLocation2 = glGetUniformLocation(shaderProgram2, "ourColor");

        // 4. draw the object
        glUseProgram(shaderProgram1);
        glUniform4f(vertexColorLocation1, 0.0f, greenValue1, 0.0f, 1.0f);
        glBindVertexArray(VAO1);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

        glUseProgram(shaderProgram2);
        glUniform4f(vertexColorLocation2, 0.0f, greenValue2, 0.0f, 1.0f);
        glBindVertexArray(VAO2);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

        // check and call events, and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // deallocate all resources
    glDeleteVertexArrays(1, &VAO1);
    glDeleteBuffers(1, &VBO1);
    glDeleteVertexArrays(1, &VAO2);
    glDeleteBuffers(1, &VBO2);
    glDeleteProgram(shaderProgram1);

    // terminate GLFW
    glfwTerminate();
}