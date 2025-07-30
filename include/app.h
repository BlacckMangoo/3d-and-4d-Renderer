#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>


class App {

public:
    int width;
    int height;
    GLFWwindow* window;

	App(int width, int height) : width(width), height(height), window(nullptr) {}


    void Init();
	void Run();
    void Clear();

};