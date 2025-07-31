
#pragma once
#include <iostream>
#include <app.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <Renderer/mesh.h>
#include <Renderer/resourceManager.h>
#include <Renderer/shader.h>
#include <Renderer/camera.h>
#include <Renderer/primitives.h>

#include <FourDMath/fourDRotation.h>
Shader unlitshader; 
Shader fourDUnlitStereographicShader;

Mesh<glm::vec3> rectangleMesh(rectanglePrimitive);
Mesh<glm::vec3> triangleMesh(trianglePrimitive);
Mesh<glm::vec3> cubeMesh(cubePrimitive);
Mesh<glm::vec4> tesseractMesh(tesseractPrimitive);

Camera camera;





void App::Init()
{

	if (!glfwInit())
	{
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return;
	}

	window = glfwCreateWindow(width, height, "App", nullptr, nullptr);
	if (!window)
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(window);
	
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD" << std::endl;
		return;
	}

	glViewport(0, 0, width, height);

	glEnable(GL_DEPTH_TEST);
	
	cubeMesh.Upload();
	tesseractMesh.Upload();
	

	//Load shaders

	unlitshader = ResourceManager::LoadShader(
		RESOURCES_PATH "/unlit.vert", RESOURCES_PATH "/unlit.frag", nullptr, "unlitShader");
	fourDUnlitStereographicShader = ResourceManager::LoadShader(
		RESOURCES_PATH "/stereographicallyproject.vert", RESOURCES_PATH "/unlit.frag", nullptr, "stereographicallyProjectedShader");
	
}

void App::Run()
{

	while (!glfwWindowShouldClose(window))
	{

		float time = glfwGetTime();
		
		glClearColor(0, 0, 0, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Create 4D rotation matrix
		float angleXY = time * 0.5f;  
		float angleZW = time * 0.3f;  
		glm::mat4 rotation4D = Rotation4D::doubleRotation(angleXY, angleZW);
		
		//unlitshader.Use();
		glm::mat4 projection = camera.GetProjectionMatrix();
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.3, 0.3, 0.3));
		fourDUnlitStereographicShader.Use();
		fourDUnlitStereographicShader.SetVector3f("uColor", glm::vec3(1.0f, 0.0f, 0.0f));
		fourDUnlitStereographicShader.SetMatrix4("uProjection", projection);
		fourDUnlitStereographicShader.SetMatrix4("uRotation4D", rotation4D);
		fourDUnlitStereographicShader.SetMatrix4("uView", view);
		fourDUnlitStereographicShader.SetMatrix4("uModel", model);

		

		
		tesseractMesh.DrawMesh();

		
		glfwSwapBuffers(window);
		glfwPollEvents();


		//handle Input 

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

}

void App::Clear()
{
	if (window)
	{
		glfwDestroyWindow(window);
		window = nullptr;
	}

	glfwTerminate();
}