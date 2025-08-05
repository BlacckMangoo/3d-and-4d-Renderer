#pragma once
#include <GLFW/glfw3.h>
#include <Renderer/camera.h>


class  InputManger {

public:
    Camera* camera ;

    InputManger(Camera* cam ): camera((cam)){};


    static void CheckInput(Camera& camera,GLFWwindow* window);



};



