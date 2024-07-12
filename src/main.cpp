#include <spdlog/spdlog.h>
#include <glad/glad.h>
#include <glfw/glfw3.h>

#include "context.h"

void OnWindowSizeCallback(GLFWwindow* window, int width, int height) {
    SPDLOG_INFO("Window size changed: {} {}", width, height);
    glViewport(0, 0, width, height);
}

int main(int argv, char* argc[]) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        SPDLOG_INFO("Failed to create GLFW window");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        SPDLOG_INFO("Failed to initialize GLAD");
        return -1;
    }

    OnWindowSizeCallback(window, WINDOW_WIDTH, WINDOW_HEIGHT);
    glfwSetWindowSizeCallback(window, OnWindowSizeCallback);

    ContextUPtr context = Context::Create();

    while(!glfwWindowShouldClose(window))
    {
        context->Render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}