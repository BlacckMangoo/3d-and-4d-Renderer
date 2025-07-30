
#pragma once
#include <iostream>
#include <app.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <mesh.h>
#include <resourceManager.h>
#include <shader.h>
#include <primitives.h>
Shader unlitshader; 

Mesh rectangleMesh(rectanglePrimitive);
Mesh triangleMesh(trianglePrimitive);
Mesh cubeMesh(cubePrimitive);




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
		"resources/unlit.vert", "resources/unlit.frag", nullptr, "unlitShader");
	

}

void App::Run()
{

	while (!glfwWindowShouldClose(window))
	{
	
		glClearColor(0, 0, 0, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		
		unlitshader.Use();
		cubeMesh.Draw();
		
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
	rectangleMesh.Clear();
	glfwTerminate();
}