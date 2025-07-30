#pragma once

#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <shader.h>
#include  <utils.h>




class Mesh {
public:


    Mesh(Primitive primitive);

    void Upload();   
    void Draw();        
    void Clear();      

    ~Mesh();          

private:
    GLuint VAO = 0, VBO = 0, EBO = 0;
    unsigned int vertexCount = 0;
    unsigned int indexCount = 0;
    bool useIndices = false;

    std::vector<MeshVertex> vertices; 
    std::vector<unsigned int> indices; 

    void SetupAttributes();
};
