
#include <iostream>
#include <app.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Renderer/camera.h>
#include <inputManager.h>
#include <Renderer/shaderList.h>
#include "timeManger.h"


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
	glfwSwapInterval(1); //enables vsync
	
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD" << std::endl;
		return;
	}


	glViewport(0, 0, width, height);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);

	InputManager::SetupMouseInput(window, camera);
	GlobalShaders::LoadAll();


	TimeManager::Init();

}

void App::Run()
{

	while (!glfwWindowShouldClose(window))
	{
		TimeManager::Update();
		InputManager::CheckInput(camera, window);

		glClearColor(0, 0, 0, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		glfwSwapBuffers(window);
		glfwPollEvents();


		//handle Input
		InputManager::CheckInput(camera,window);
		
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

