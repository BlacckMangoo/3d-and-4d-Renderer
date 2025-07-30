#include <camera.h>
#include <glm/gtc/matrix_transform.hpp>

glm::mat4 Camera::GetProjectionMatrix() const 
{
	glm::mat4 projection = glm::perspective(glm::radians(fov), aspect, nearClip, farClip);
	return projection; 
}

glm::mat4 Camera::GetViewMatrix() const
{
	glm::mat4 view = glm::lookAt(position, position + front, up);
	return view;
}