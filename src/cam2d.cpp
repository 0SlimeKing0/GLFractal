#include "cam2d.h"

float ln2 = log(2);

Cam2DUPtr Cam2D::CreateFromWindow(GLFWwindow* window) {
    return Cam2DUPtr(new Cam2D(window));
}

void Cam2D::ProcessInput() {
    float currentFrame = glfwGetTime();
    float delta = currentFrame - lastFrame;
    lastFrame = currentFrame;

    float scale = pow(2, zoom) * delta;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        pos += vec3(0.0f, camSpeed * scale, 0.0f);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        pos += vec3(-camSpeed * scale, 0.0f, 0.0f);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        pos += vec3(0.0f, -camSpeed * scale, 0.0f);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        pos += vec3(camSpeed * scale, 0.0f, 0.0f);
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        zoom += -camSpeed * delta;
        pos.z = pow(2, zoom);
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        zoom += camSpeed * delta;
        pos.z = pow(2, zoom);
    }
}