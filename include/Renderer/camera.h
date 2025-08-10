#pragma once
#include <glm/glm.hpp>


class Camera {
public:

    glm::vec3 position = {0,0,-3};
    glm::vec3 front = {0,0,-1};
    glm::vec3 up = {0,1,0};
	glm::vec3 right = {0,0,1};
    float fov = 45.0f;
    float aspect = static_cast<float>(16.0f/9.0f);
    float nearClip ;
    float farClip;

	float cameraMovementSpeed = 0.001;




	float yaw   = -90.0f;
	float pitch =  0.0f;



	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f),
		glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f),
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3 right = glm::vec3(0.0f, 0.0f, 1.0f),
		float fov = 45.0f,
		float aspect = 16.0f / 9.0f,
		float nearClip = 0.001f,
		float farClip = 100000.0f,
		float cameraMovementSpeed = 12.0f ,
		float yaw = -90.0f,
		float pitch = 0.0f)
		: position(position), front(front), up(up), fov(fov), aspect(aspect), nearClip(nearClip), farClip(farClip) ,cameraMovementSpeed(cameraMovementSpeed) , yaw(yaw),pitch(pitch),right(right){
	}



    glm::mat4 GetViewMatrix() const;
    glm::mat4 GetProjectionMatrix() const;

};