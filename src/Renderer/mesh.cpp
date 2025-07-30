#include <mesh.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <resourceManager.h>
#include <iostream>





Mesh::Mesh(Primitive primitive)
	: vertices(primitive.vertices), indices(primitive.indices)
{
	vertexCount = static_cast<unsigned int>(vertices.size());
	indexCount = static_cast<unsigned int>(indices.size());
	useIndices = indexCount > 0;
	if (useIndices) {
		this->indices = primitive.indices;
	}
	else {
		this->indices.clear();
	}
}



Mesh::~Mesh()
{
	Clear();
}




void Mesh::Upload()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    if (useIndices) glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    // Upload vertex data
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER,
		vertices.size() * sizeof(MeshVertex),
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

void Mesh::DrawMesh()
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





void Mesh::Clear() {
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


void Mesh::SetupAttributes()
{
    glEnableVertexAttribArray(0); // Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex),
		(void*)offsetof(MeshVertex, position));

    glEnableVertexAttribArray(1); // Normal
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex),
		(void*)offsetof(MeshVertex, normal));
  
}