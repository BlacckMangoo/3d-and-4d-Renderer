
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
#include <InputManger.h>


Shader unlitshader; 
Shader fourDUnlitStereographicShader;



Mesh<glm::vec3> rectangleMesh(rectanglePrimitive);
Mesh<glm::vec3> triangleMesh(trianglePrimitive);
Mesh<glm::vec3> cubeMesh(cubePrimitive);
Mesh<glm::vec4> tesseractMesh(tesseractPrimitive);
Mesh<glm::vec3> circleMesh(CircleGenerator(0.5f, 32));
Mesh<glm::vec3> torusMesh(GenerateTorus(32,32,0.1f,0.5f ,glm::vec3 {0,0,0}));


Camera camera;

InputManger input_manger(&camera);

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
	circleMesh.Upload();
	torusMesh.Upload();
	

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


		glm::mat4 projection = camera.GetProjectionMatrix();
		glm::mat4 view = camera.GetViewMatrix();


		//render Tesseract

		float angleXY = time * 0.5f;
		float angleZW = time * 0.3f;
		glm::mat4 rotation4D = Rotation4D::doubleRotation(angleXY, angleZW);



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

		unlitshader.Use();
		unlitshader.SetVector3f("uColor", glm::vec3(1.0f, 0.0f, 0.0f));
		unlitshader.SetMatrix4("uProjection", projection);
		unlitshader.SetMatrix4("uView", view);

		glm::mat4 model2 = glm::mat4(1.0f);
		model2 = glm::translate(model2, glm::vec3(2.0f, 0.0f, 0.0f));
		model2 = glm::scale(model2, glm::vec3(0.8, 0.8, 0.8));
		model2 = glm::rotate(model2, glm::radians(39.0f)*time, glm::vec3(1.0f, 1.0f, 1.0f));

		unlitshader.SetMatrix4("uModel", model2);

		torusMesh.DrawMesh();
		
		glfwSwapBuffers(window);
		glfwPollEvents();


		//handle Input
		InputManger::CheckInput(camera,window);
		
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

