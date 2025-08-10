
#pragma once
#include <vector>
#include <Renderer/shader.h>
#include <Renderer/camera.h>
#include <memory>


struct Particle
{
    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec3 acceleration;
    float mass;

};

class Galaxy {

public:

    Galaxy( int  particleCount) ;
    ~Galaxy();

    float  galaxyRadius ;
    glm::vec3 centre ;
    void Draw(Camera& camera);
    void Update(float dt);
    glm::vec3 galaxyCenter;

private:
    size_t particleCount;

    std::vector<Particle> particles;


    unsigned int vao;
    unsigned int vbo;


};



