#define GLEW_DLL
#define GLFW_DLL
#include <iostream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Shader.h"   // май библиотека
#include "Model.h"
#include "glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
// Положение
//glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 0.0f);
// Направление камеры
//glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
//glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
// Правый вектор
//glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0);
//glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
// Извлечь вектор
//glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);

//view = glm::lookAt(cameraPos, cameraTarget, cameraUp);
// Матрица проекции

// Матрицая видовая
//glm::mat4 view = glm::lookAt(glm::vec3 const& eye, glm::vec3 const& center, glm::vec3 const& up);

glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 4.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

const unsigned int SCR_WIDTH = 1024;
const unsigned int SCR_HEIGTH = 768;

float lastX = SCR_WIDTH / 2, lastY = SCR_HEIGTH / 2;

bool firstMouse = true;
float yaw = -90.0f;
float pitch = 0.0f;
float fov = 45.0f;
float deltaTime = 0.0f;
float lastFrame = 0.0f;

void framebuffer_size_callback(GLFWwindow* window, int width, int heigth) {
    glViewport(0, 0, width, heigth);
}
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;
    float sensitivity = 0.1f;
    xoffset += sensitivity;
    yoffset += sensitivity;
    yaw += xoffset;
    pitch += yoffset;
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    fov -= (float)yoffset;
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 45.0f)
        fov = 45.0f;
}

float vertex[] = { 0.0f, 0.5f, 0.2f,
                  -0.5f, 0.2f, 0.3f,
                  -0.3f, -0.4f, 0.4f,
                   0.3f, -0.4f, 0.4f,
                   0.5f, 0.2f, 0.5f };
//Рубрика эксперименты с движением камеры
void processInput(GLFWwindow* win) {
    const float cameraSpeed = 2.5f * deltaTime;
  /*  if (glfwGetKey(win, GLFW_KEY_UP) == GLFW_PRESS) 
        cameraPosition += cameraSpeed * cameraFront;
    if (glfwGetKey(win, GLFW_KEY_DOWN) == GLFW_PRESS) 
        cameraPosition -= cameraSpeed * cameraFront;
    if (glfwGetKey(win, GLFW_KEY_LEFT) == GLFW_PRESS) 
        cameraPosition -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(win, GLFW_KEY_RIGHT) == GLFW_PRESS) 
        cameraPosition += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
  */if (glfwGetKey(win, GLFW_KEY_W) == GLFW_PRESS) //w
        cameraPosition += cameraSpeed * cameraFront;
    if (glfwGetKey(win, GLFW_KEY_S) == GLFW_PRESS) //s
        cameraPosition -= cameraSpeed * cameraFront;
    if (glfwGetKey(win, GLFW_KEY_A) == GLFW_PRESS) //a
        cameraPosition -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(win, GLFW_KEY_D) == GLFW_PRESS) //d
        cameraPosition += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}
int main() {
    std::cout << "я русский - со мной бог" << std::endl;

    //glm::mat4 viev = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);

    // Инициализация GLFW
    if (!glfwInit()) {
        std::cerr << "ERROR glfwInit\n";
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGTH, "3d chtoby rabotalo", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -2;
    }
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    glewInit();

    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindVertexArray(VAO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    Shader shader("vertex.txt", "fragment.txt");
    Model myModel("lr3var5.obj");
    if (myModel.meshes.empty())
        std::cout << "The model has no meshes" << std::endl;
    // Главный цикл
    while (!glfwWindowShouldClose(window)) {
        float time = (float)glfwGetTime();

        glClearColor(0.5f, 0.2f, 0.7f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        processInput(window);
        
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glm::mat4 projection = glm::perspective(glm::radians(fov), (float)SCR_WIDTH/(float)SCR_HEIGTH, 0.1f, 100.0f);
        glm::mat4 view = glm::lookAt(cameraPosition, cameraPosition+cameraFront, cameraUp);
        glm::mat4 transform = glm::mat4(1.0f);
        glm::mat4 model = glm::mat4(1.0f);

        
        shader.SetUniform("model", glm::value_ptr(model),GL_FALSE);
        shader.SetUniform("view", glm::value_ptr(view), GL_FALSE);
        shader.SetUniform("projection", glm::value_ptr(projection), GL_FALSE);
        shader.SetUniform("transform", glm::value_ptr(transform), GL_FALSE);
        shader.SetUniform("lightColor", 0.5f, 0.6f, 0.4f);
        myModel.Draw();
        shader.Use();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}


