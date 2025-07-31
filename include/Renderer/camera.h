#include <glm/glm.hpp>


class Camera {
public:

    glm::vec3 position ;
    glm::vec3 front;
    glm::vec3 up;
    float fov;
    float aspect;
    float nearClip;
    float farClip;
	float cameraMovementSpeed;

	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f),
		glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f),
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
		float fov = 45.0f,
		float aspect = 16.0f / 9.0f,
		float nearClip = 0.1f,
		float farClip = 100.0f,
		float cameraMovementSpeed = 0.01f)
		: position(position), front(front), up(up), fov(fov), aspect(aspect), nearClip(nearClip), farClip(farClip) ,cameraMovementSpeed(cameraMovementSpeed){
	}



    glm::mat4 GetViewMatrix() const;
    glm::mat4 GetProjectionMatrix() const;

};