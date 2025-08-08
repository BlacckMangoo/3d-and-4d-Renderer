
#pragma once
#include <vector>
#include <Renderer/shader.h>
#include <Renderer/camera.h>
struct Particle
{
    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec3 acceleration;
    float mass;

};

class Galaxy {

public:

    Galaxy( size_t particleCount , Shader& shader) ;
    ~Galaxy();

    void Update(float dt );
    void Draw(Camera& camera);

private:
    size_t particleCount;
    std::vector<Particle> particles;


    unsigned int vao;
    unsigned int vbo;
    Shader& shader;

};



