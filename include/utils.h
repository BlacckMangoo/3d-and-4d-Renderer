#pragma once 
#include <glm/glm.hpp>


struct MeshVertex {
    glm::vec3 position;
    glm::vec3 normal;
    
};



struct Primitive {

    const std::vector<MeshVertex> vertices;
    const std::vector<unsigned int> indices;

};

struct Transform {
    glm::vec3 position = {};
    glm::vec3 rotation = {}; // Euler angles in degrees
    glm::vec3 scale = glm::vec3(1.0f);
};