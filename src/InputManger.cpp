#include "InputManager.h"

Camera* InputManager::s_camera = nullptr;

void InputManager::SetupMouseInput(GLFWwindow* window, Camera& camera)
{
    s_camera = &camera;
    glfwSetCursorPosCallback(window, mouse_callback_static);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void InputManager::mouse_callback_static(GLFWwindow* window, double xpos, double ypos)
{
    static bool firstMouse = true;
    static float lastX = 0.0f;
    static float lastY = 0.0f;
    static float sensitivity = 0.1f;

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    xoffset *= sensitivity;
    yoffset *= sensitivity;

    s_camera->yaw += xoffset;
    s_camera->pitch += yoffset;

    if (s_camera->pitch > 89.0f) s_camera->pitch = 89.0f;
    if (s_camera->pitch < -89.0f) s_camera->pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(s_camera->yaw)) * cos(glm::radians(s_camera->pitch));
    front.y = sin(glm::radians(s_camera->pitch));
    front.z = sin(glm::radians(s_camera->yaw)) * cos(glm::radians(s_camera->pitch));
    s_camera->front = glm::normalize(front);

    s_camera->right = glm::normalize(glm::cross(s_camera->front, glm::vec3(0.0f, 1.0f, 0.0f)));
    s_camera->up = glm::normalize(glm::cross(s_camera->right, s_camera->front));
}

void InputManager::CheckInput(Camera& camera, GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.position += camera.front * camera.cameraMovementSpeed;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.position -= camera.front * camera.cameraMovementSpeed;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.position -= camera.right * camera.cameraMovementSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.position += camera.right * camera.cameraMovementSpeed;
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        camera.position += camera.up * camera.cameraMovementSpeed;
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        camera.position -= camera.up * camera.cameraMovementSpeed;

    static bool mouseToggle = false;
    if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS && !mouseToggle)
    {
        static bool mouseCaptured = true;
        mouseCaptured = !mouseCaptured;

        if (mouseCaptured)
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        else
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

        mouseToggle = true;
    }

    if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_RELEASE)
        mouseToggle = false;
}
