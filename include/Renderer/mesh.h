#pragma once

#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <Renderer/shader.h>
#include <Renderer/primitives.h>

// 3d and 4d meshes templated 

template <typename T>
class Mesh {
public:

    Mesh(const Primitive<T>& primitive);


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

    std::vector<T> vertices; 
    std::vector<unsigned int> indices; 

    void SetupAttributes();
};

// Template function definitions moved from mesh.cpp

template<typename T>
Mesh<T>::Mesh(const Primitive<T>& primitive)
    : vertices(primitive.vertices), indices(primitive.indices)
{
    vertexCount = static_cast<unsigned int>(vertices.size());
    indexCount = static_cast<unsigned int>(indices.size());
    useIndices = !indices.empty();
    if (useIndices) {
        std::cout << "Mesh created with " << vertexCount << " vertices and " << indexCount << " indices." << std::endl;
    }
    else {
        std::cout << "Mesh created with " << vertexCount << " vertices." << std::endl;
    }
}

template<typename T>
Mesh<T>::~Mesh()
{
    Clear();
}

template <typename T>
void Mesh<T>::Upload()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    if (useIndices) glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    // Upload vertex data
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER,
        vertices.size() * sizeof(T),
        vertices.data(),
        GL_STATIC_DRAW);

    // Upload index data if present
    if (useIndices) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,
            indices.size() * sizeof(unsigned int),
            indices.data(),
            GL_STATIC_DRAW);
        // EBO is automatically bound to VAO when bound while VAO is active
        std::cout << "Uploaded " << indices.size() << " indices to EBO" << std::endl;
    }
    SetupAttributes();
}

template <typename T>
void Mesh<T>::DrawMesh()
{
    glBindVertexArray(VAO);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    if (useIndices) {
        glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
        // Check for OpenGL errors
        GLenum error = glGetError();
        if (error != GL_NO_ERROR) {
            std::cerr << "OpenGL error in DrawMesh: " << error << std::endl;
        }
    }
    else {
        glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    }
    glBindVertexArray(0);
}

template <typename T>
void Mesh<T>::Clear() {
    if (EBO) {
        glDeleteBuffers(1, &EBO);
        EBO = 0;
    }
    if (VBO) {
        glDeleteBuffers(1, &VBO);
        VBO = 0;
    }
    if (VAO) {
        glDeleteVertexArrays(1, &VAO);
        VAO = 0;
    }
}

template <typename T>
void Mesh<T>::SetupAttributes()
{
    // Position
    glEnableVertexAttribArray(0); 
    if constexpr (std::is_same_v<T, glm::vec3>) {
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(T), (void*)0);
    } else if constexpr (std::is_same_v<T, glm::vec4>) {
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(T), (void*)0);
    }
}
