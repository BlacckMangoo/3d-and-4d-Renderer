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
    void DrawMesh();        
    void Clear();      

    ~Mesh();
    
    // Getters for debugging
    unsigned int GetVertexCount() const { return vertexCount; }
    unsigned int GetIndexCount() const { return indexCount; }          

private:
    GLuint VAO = 0, VBO = 0, EBO = 0;
    unsigned int vertexCount = 0;
    unsigned int indexCount = 0;
    bool useIndices = false;

    std::vector<MeshVertex> vertices; 
    std::vector<unsigned int> indices; 

    void SetupAttributes();
};
