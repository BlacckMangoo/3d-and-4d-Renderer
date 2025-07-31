
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
Shader unlitshader; 

Mesh rectangleMesh(rectanglePrimitive);
Mesh triangleMesh(trianglePrimitive);
Mesh cubeMesh(cubePrimitive);


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
	

	//Load shaders

	unlitshader = ResourceManager::LoadShader(
		RESOURCES_PATH "/unlit.vert", RESOURCES_PATH "/unlit.frag", nullptr, "unlitShader");

	
}

void App::Run()
{

	while (!glfwWindowShouldClose(window))
	{

		float time = glfwGetTime();

	
		
	
		glClearColor(0, 0, 0, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
	
		unlitshader.Use();
		glm::mat4 projection = camera.GetProjectionMatrix();
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::rotate(model, time * glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // Rotate around Y-axis
		model = glm::scale(model, glm::vec3(0.3, 0.3, 0.3));
		// Set shader uniforms


		unlitshader.SetMatrix4("uProjection", projection);
		unlitshader.SetMatrix4("uView", view);
		unlitshader.SetMatrix4("uModel", model);
		unlitshader.SetVector3f("uColor", glm::vec3(1.0f, 0.0f, 0.0f)); // Red

		cubeMesh.DrawMesh();
		
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