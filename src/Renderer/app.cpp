
#pragma once
#include <iostream>
#include <app.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <mesh.h>
#include <resourceManager.h>
#include <shader.h>
#include <camera.h>
#include <primitives.h>
Shader unlitshader; 

Mesh rectangleMesh(rectanglePrimitive);
Mesh triangleMesh(trianglePrimitive);
Mesh cubeMesh(cubePrimitive);
Mesh tesseractMesh(tesseractPrimitive);


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

	
}

void App::Run()
{

	while (!glfwWindowShouldClose(window))
	{
	
		glClearColor(0, 0, 0, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		float time = (float)glfwGetTime();
		unlitshader.Use();
		glm::mat4 projection = camera.GetProjectionMatrix();
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::rotate(model, time * glm::radians(50.0f), glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.3, 0.3, 0.3));
		// Set shader uniforms


		unlitshader.SetMatrix4("uProjection", projection);
		unlitshader.SetMatrix4("uView", view);
		unlitshader.SetMatrix4("uModel", model);
		unlitshader.SetVector3f("uColor", glm::vec3(1.0f, 0.0f, 0.0f)); // Red

		tesseractMesh.DrawMesh();
		
		glfwSwapBuffers(window);
		glfwPollEvents();
		
	}

}

void App::Clear()
{
	if (window)
	{
		glfwDestroyWindow(window);
		window = nullptr;
	}
	tesseractMesh.Clear();
	glfwTerminate();
}