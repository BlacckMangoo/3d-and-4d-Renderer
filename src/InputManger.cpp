
#include "../include/InputManger.h"

void InputManger::CheckInput(Camera& camera, GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        camera.position += camera.front * camera.cameraMovementSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        camera.position -= camera.front * camera.cameraMovementSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        camera.position -= glm::normalize(glm::cross(camera.front, camera.up)) * camera.cameraMovementSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        camera.position += glm::normalize(glm::cross(camera.front, camera.up)) * camera.cameraMovementSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        camera.position += camera.up * camera.cameraMovementSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
        camera.position -= camera.up * camera.cameraMovementSpeed;
    }
}







