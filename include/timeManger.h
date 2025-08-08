#pragma once
#include <GLFW/glfw3.h>

class TimeManager {
public:
    static void Init() {
        lastTime = glfwGetTime();
        deltaTime = 0.0f;
        totalTime = 0.0f;
    }

    static void Update() {
        double currentTime = glfwGetTime();
        deltaTime = static_cast<float>(currentTime - lastTime);
        lastTime = currentTime;
        totalTime += deltaTime;
    }

    static float DeltaTime() { return deltaTime; }
    static float TotalTime() { return totalTime; }

private:
    static inline double lastTime = 0.0;
    static inline float deltaTime = 0.0f;
    static inline float totalTime = 0.0f;
};
