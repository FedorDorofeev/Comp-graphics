#define GLEW_DLL
#define GLFW_DLL

#include <stdio.h>
#include "glew.h"
#include "glfw3.h"
#include <iostream>
#include "Shader.h"

float points[] = {
     0.0f,  0.5f, 0.0f,
     -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
};

GLuint indices[] = {
    0, 1, 2
};

int main() {

    if (!glfwInit()) {
        fprintf(stderr, "ERR: could not start GLFW3.\n");
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_FALSE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    GLFWwindow* window = glfwCreateWindow(512, 512, "Trapezoid", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;

    
    GLenum ret = glewInit();
    if (ret != GLEW_OK) {
        fprintf(stderr, "ERR: %s\n", glewGetErrorString(ret));
        return -1;
    }

    GLuint VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);


    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    Shader shader("vert_shader.glsl", "frag_shader.glsl");

    while (!glfwWindowShouldClose(window)) {

        glClearColor(0.2f, 0.3f, 0.4f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        float timeValue = (float)glfwGetTime();

        float red = (sin(timeValue) / 2.0f) + 0.5f;
        float green = (cos(timeValue) / 2.0f) + 0.5f;
        float blue = (sin(timeValue + 3.14f) / 2.0f) + 0.5f;


        shader.Use();
        shader.SetUniform("ourColor", red, green, blue, 1.0f);

        glBindVertexArray(VAO);

        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}