
#include <iostream>
#include <app.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Renderer/camera.h>
#include <inputManager.h>
#include <Renderer/shaderList.h>
#include "timeManger.h"
#include <Renderer/galaxy.h>
#include<memory>


Camera camera;

std::unique_ptr<Galaxy> galaxy;


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
	galaxy = std::make_unique<Galaxy>(1000);


	TimeManager::Init();


}

void App::Run()
{

	while (!glfwWindowShouldClose(window))
	{
		TimeManager::Update();
		float dt = TimeManager::DeltaTime();


		InputManager::CheckInput(camera, window);

		glClearColor(0, 0, 0, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		galaxy->Update(dt);
		galaxy->Draw(camera);


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

	glfwTerminate();
}

