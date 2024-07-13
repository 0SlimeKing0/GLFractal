#ifndef __CAM2D_H__
#define __CAM2D_H__

#include "common.h"
#include <functional>

using namespace glm;

CLASS_PTR(Cam2D)
class Cam2D {
    public:
        static Cam2DUPtr CreateFromWindow(GLFWwindow* window);
        void ProcessInput();

        vec3 pos = vec3(0.0f, 0.0f, 1.0f);
    private:
        Cam2D(GLFWwindow* _window) { window = _window; };

        GLFWwindow* window;

        float camSpeed = 2.0f;
        float zoom = 0.0f;

        float lastFrame = glfwGetTime();
};

#endif