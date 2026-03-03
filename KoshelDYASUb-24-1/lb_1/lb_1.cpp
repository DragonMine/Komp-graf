#define GLEW_DLL
#define GLFW_DLL
#include <iostream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"

int main()
{
    std::cout << "SLAVA BOGY Z!" << std::endl;

    glfwInit();
    if (!glfwInit()) {
        fprintf(stderr, "ERROR glfwInit:\n");
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 1.0);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0.0);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* MyWindow;
    MyWindow = glfwCreateWindow(512, 512, "MainOkno", NULL, NULL);

    if (!MyWindow) {
        glfwTerminate();
        return -2;
    }

    glfwMakeContextCurrent(MyWindow);
    glewExperimental = GL_TRUE;

    glewInit();

    while (!glfwWindowShouldClose(MyWindow)) {
        glClearColor(0.5f, 0.2f, 0.7f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_POLYGON);
        glColor3f(1.0, 1.0, 1.0);
        glVertex2f(0.0, 0.5);   // Верхняя 
        glVertex2f(-0.5, 0.2);  // Левая верхняя
        glVertex2f(-0.3, -0.4); // Левая нижняя
        glVertex2f(0.3, -0.4);  // Правая нижняя
        glVertex2f(0.5, 0.2);   // Правая верхняя
        glEnd();

        glfwSwapBuffers(MyWindow);
        glfwPollEvents();
    }

    glfwTerminate();
}