#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

#include "shader.h"

#define PI 3.14159265f

void framebuffer_resize_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main() {
    // setup start
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Reading Shaders From files", NULL, NULL);

    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << '\n';
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << '\n';
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_resize_callback);

    Shader shader("vertexShader.glsl", "fragmentShader.glsl");

    // buffer start

    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };	

    unsigned int VBO, VAO; //, EBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // vertex attributes linking
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    // buffer end
    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        // draw start

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        float timeValue = glfwGetTime();
        // with the red green and blue values being 120 degres apart the
        // result should pass trough all the colors of the color wheel
        // max(sin(timeValue + 0/3 * PI) + 0.5, 0) * 2/3

        //float redValue   = std::max((float)sin(timeValue + (0.f/3.f) * PI) + 0.5f, 0.0f) * 2/3; 
        //float greenValue = std::max((float)sin(timeValue + (2.f/3.f) * PI) + 0.5f, 0.0f) * 2/3;
        //float blueValue  = std::max((float)sin(timeValue + (4.f/3.f) * PI) + 0.5f, 0.0f) * 2/3;

        //float redValue   = std::min(std::max((float)sin(timeValue + (0.f/3.f) * PI) + 0.5f, 0.0f), 1.0f); 
        //float greenValue = std::min(std::max((float)sin(timeValue + (2.f/3.f) * PI) + 0.5f, 0.0f), 1.0f);
        //float blueValue  = std::min(std::max((float)sin(timeValue + (4.f/3.f) * PI) + 0.5f, 0.0f), 1.0f);

        float redValue   = (sin(timeValue + (0.0f / 3 * PI)) + 1.0f) / 2.0f;
        float greenValue = (sin(timeValue + (2.0f / 3 * PI)) + 1.0f) / 2.0f;
        float blueValue  = (sin(timeValue + (4.0f / 3 * PI)) + 1.0f) / 2.0f;

        int vertexColorLocation = glGetUniformLocation(shader.ID, "ourColor");
        shader.use();
        glUniform4f(vertexColorLocation, redValue, greenValue, blueValue, 1.0f);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // draw end
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void framebuffer_resize_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

