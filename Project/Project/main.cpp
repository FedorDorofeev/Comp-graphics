#include <iostream>
#include <glew.h>
#include <glfw3.h>

int main() {

    if (!glfwInit()) {
        fprintf(stderr, "ERROR: could not start GLFW3. \n");
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 1);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    /*glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    */

    GLFWwindow* window = glfwCreateWindow(512, 512, "Mainwindow", NULL, NULL);

    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;

    GLenum ret = glewInit();

    if (GLEW_OK != ret) {
        fprintf(stderr, "Error: %s \n", glewGetErrorString(ret));
        return 1;
    }

    glClearColor(0.2f, 0.3f, 0.4f, 0.0f);

    while (!glfwWindowShouldClose(window)) {

        glClear(GL_COLOR_BUFFER_BIT);
        glBegin(GL_TRIANGLES);

        //Треугольник
        glColor3f(0.5f, 0.5f, 0.0f);
        glVertex2f(0.0f, 0.5f);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f(0.5f, -0.5f);

        glEnd();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    const GLubyte* version_str = glGetString(GL_VERSION);
    const GLubyte* device_str = glGetString(GL_RENDERER);

    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
    printf("This version OpenGL running is %s\n", version_str);
    printf("This device OpenGL running is %s\n", device_str);


    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}