#pragma once

#include <GLFW/glfw3.h>
#include <Renderer/camera.h>

class InputManager
{
private:
    static Camera* s_camera;

public:
    static void SetupMouseInput(GLFWwindow* window, Camera& camera);
    static void mouse_callback_static(GLFWwindow* window, double xpos, double ypos);
    static void CheckInput(Camera& camera, GLFWwindow* window);
};