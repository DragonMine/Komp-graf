#define GLEW_DLL
#define GLFW_DLL
#include <iostream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Shader.h"   // май библиотека

float vertex[] = { 0.0f, 0.5f, 0.2f,
                  -0.5f, 0.2f, 0.3f,
                  -0.3f, -0.4f, 0.4f,
                   0.3f, -0.4f, 0.6f,
                   0.5f, 0.2f, 0.5f };

int main() {
    std::cout << "я русский - со мной бог" << std::endl;

    // Инициализация GLFW
    if (!glfwInit()) {
        std::cerr << "ERROR glfwInit\n";
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(512, 512, "Shader Library Demo", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -2;
    }
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    glewInit();

    // Создание VAO и VBO
    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindVertexArray(VAO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Использование нашей библиотеки Shader
    Shader shader("vertex.vert", "fragment.frag");

    // Главный цикл
    while (!glfwWindowShouldClose(window)) {
        float time = (float)glfwGetTime();

        glClearColor(0.5f, 0.2f, 0.7f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.Use();
        shader.SetUniform("u_time", time);   // одна строка — передача uniform

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 5);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Очистка
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();
    return 0;
}