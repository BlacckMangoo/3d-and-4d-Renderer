#pragma once

#include <vector>
#include <Renderer/mesh.h>
#include <glm/glm.hpp>
#include <type_traits>
//3D primitive
#include <iostream>


template <typename T>
struct Primitive {
    static_assert(std::is_same_v<T, glm::vec3> || std::is_same_v<T, glm::vec4>,
        "Primitive must use glm::vec3 or glm::vec4 for vertices");

    std::vector<T> vertices;
    std::vector<unsigned int> indices;
};

Primitive < glm::vec3> inline  rectanglePrimitive = {

    //vertices
    {
        { -0.5f, -0.5f, 0.0f }, 
		 {  0.5f, -0.5f, 0.0f }, 
		{  0.5f,  0.5f, 0.0f }, 
		 { -0.5f,  0.5f, 0.0f }, 

},
	
	//indexes
	 {
	0, 1, 2,
	2, 3, 0
} };

Primitive<glm::vec3> inline   trianglePrimitive = {
	//vertices 
	{
         { -0.5f, -0.5f, 0.0f },
	{  0.5f, -0.5f, 0.0f },
	{  0.0f,  0.5f, 0.0f },
},
//indexes
 {
0, 1, 2
} };



Primitive <glm::vec3> inline  cubePrimitive = {
    // vertices
    {
        // Front face
        {-0.5f, -0.5f,  0.5f}, 
        { 0.5f, -0.5f,  0.5f}, 
        { 0.5f,  0.5f,  0.5f}, 
        {-0.5f,  0.5f,  0.5f}, 

        // Back face
        {-0.5f, -0.5f, -0.5f}, 
        { 0.5f, -0.5f, -0.5f}, 
        { 0.5f,  0.5f, -0.5f}, 
        {-0.5f,  0.5f, -0.5f}, 

        // Left face
        {-0.5f, -0.5f, -0.5f}, 
        {-0.5f, -0.5f,  0.5f}, 
        {-0.5f,  0.5f,  0.5f}, 
        {-0.5f,  0.5f, -0.5f}, 

        // Right face
        {0.5f, -0.5f, -0.5f}, 
        {0.5f, -0.5f,  0.5f}, 
        {0.5f,  0.5f,  0.5f}, 
        {0.5f,  0.5f, -0.5f}, 

        // Top face
        {-0.5f,  0.5f,  0.5f}, 
        { 0.5f,  0.5f,  0.5f}, 
        { 0.5f,  0.5f, -0.5f}, 
        {-0.5f,  0.5f, -0.5f}, 

        // Bottom face
        {-0.5f, -0.5f,  0.5f},
        { 0.5f, -0.5f,  0.5f},
        { 0.5f, -0.5f, -0.5f},
        {-0.5f, -0.5f, -0.5f},
    },

    // indices
    {
        // Front
        0, 1, 2,  2, 3, 0,
        // Back
        4, 6, 5,  6, 4, 7,
        // Left
        8, 9,10, 10,11, 8,
        // Right
       12,14,13, 14,12,15,
       // Top
      16,17,18, 18,19,16,
      // Bottom
     20,22,21, 22,20,23
  }
};


Primitive<glm::vec4> inline  tesseractPrimitive = {
    // Tesseract vertices (4D hypercube) - normalized to unit hypercube
    {
        {-1,-1,-1,-1},  // 0
        { 1,-1,-1,-1},  // 1
        {-1, 1,-1,-1},  // 2
        { 1, 1,-1,-1},  // 3
        {-1,-1, 1,-1},  // 4
        { 1,-1, 1,-1},  // 5
        {-1, 1, 1,-1},  // 6
        { 1, 1, 1,-1},  // 7
        {-1,-1,-1, 1},  // 8
        { 1,-1,-1, 1},  // 9
        {-1, 1,-1, 1},  // 10
        { 1, 1,-1, 1},  // 11
        {-1,-1, 1, 1},  // 12
        { 1,-1, 1, 1},  // 13
        {-1, 1, 1, 1},  // 14
        { 1, 1, 1, 1}   // 15
    },
    // Tesseract edges as triangulated faces (96 triangles total)
    // A tesseract has 32 edges, each edge becomes 2 triangles when rendering wireframe
    {
        // Cube 1 (w = -1): 12 edges = 24 triangles
        // Bottom face edges
        0,1,2, 1,2,3,   // bottom square
        0,2,4, 2,4,6,   // left square  
        1,3,5, 3,5,7,   // right square
        4,5,6, 5,6,7,   // top square
        // Connecting edges
        0,1,4, 1,4,5,   // front bottom to top
        2,3,6, 3,6,7,   // back bottom to top

        // Cube 2 (w = 1): 12 edges = 24 triangles  
        // Bottom face edges
        8,9,10, 9,10,11,   // bottom square
        8,10,12, 10,12,14, // left square
        9,11,13, 11,13,15, // right square  
        12,13,14, 13,14,15, // top square
        // Connecting edges
        8,9,12, 9,12,13,   // front bottom to top
        10,11,14, 11,14,15, // back bottom to top

        // Hypercube connections (8 edges = 16 triangles)
        // Connect corresponding vertices between the two cubes
        0,8,1, 8,1,9,     // connect 0-8 and 1-9
        2,10,3, 10,3,11,  // connect 2-10 and 3-11  
        4,12,5, 12,5,13,  // connect 4-12 and 5-13
        6,14,7, 14,7,15,  // connect 6-14 and 7-15

        // Additional face triangulations for complete tesseract structure
        // XY plane connections (w constant)
        0,1,8, 1,8,9,     // xy plane w=-1 to w=1
        2,3,10, 3,10,11,
        4,5,12, 5,12,13,
        6,7,14, 7,14,15,

        // XZ plane connections  
        0,4,8, 4,8,12,
        1,5,9, 5,9,13,
        2,6,10, 6,10,14,
        3,7,11, 7,11,15,

        // YZ plane connections
        0,2,8, 2,8,10,
        1,3,9, 3,9,11,
        4,6,12, 6,12,14,
        5,7,13, 7,13,15
    }
};



Primitive<glm::vec3> inline CircleGenerator(float radius, int segments, glm::vec3 centre = {0, 0, 0})
{
    std::vector<glm::vec3> vertices;
    std::vector<unsigned int> indices;

    float angleStep = 360.0f / static_cast<float>(segments);

    // Add center vertex at index 0
    vertices.push_back(centre);

    // Outer vertices
    for (int i = 0; i < segments; i++)
    {
        float angle = glm::radians(angleStep * i);
        float x = centre.x + radius * cos(angle);
        float y = centre.y + radius * sin(angle);
        vertices.emplace_back(x, y, centre.z);
    }

    // Triangles
    for (int i = 1; i < segments; i++)
    {
        indices.push_back(0);
        indices.push_back(i);
        indices.push_back(i + 1);
    }

    // Final triangle (wrap around)
    indices.push_back(0);
    indices.push_back(segments);
    indices.push_back(1);

    return {vertices, indices};

}

Primitive<glm::vec3> GenerateTorus(int segments, int rings, float innerRadius, float outerRadius, glm::vec3 centre = {0,0,0})
{
    std::vector<glm::vec3> vertices;
    std::vector<unsigned int> indices;

    // Generate vertices
    for (int ring = 0; ring < rings; ring++)
    {
        float ringAngle = 2.0f * 3.14 * ring / rings; // Angle around the major radius

        for (int segment = 0; segment < segments; segment++)
        {
            float segmentAngle = 2.0f * 3.14 * segment / segments; // Angle around the minor radius

            // parametric equation of a torus
            float x = centre.x + (outerRadius + innerRadius * cos(segmentAngle)) * cos(ringAngle);
            float y = centre.y + (outerRadius + innerRadius * cos(segmentAngle)) * sin(ringAngle);
            float z = centre.z + innerRadius * sin(segmentAngle);

            vertices.emplace_back(x, y, z);
        }
    }

    // Generate indices to connect rings
    for (int ring = 0; ring < rings; ring++)
    {
        int nextRing = (ring + 1) % rings; // Wrap around to connect last ring to first

        for (int segment = 0; segment < segments; segment++)
        {
            int nextSegment = (segment + 1) % segments; // Wrap around within each ring

            // Current ring vertices
            int current = ring * segments + segment;
            int currentNext = ring * segments + nextSegment;

            // Next ring vertices
            int next = nextRing * segments + segment;
            int nextNext = nextRing * segments + nextSegment;

            // Create two triangles for each quad
            // Triangle 1
            indices.push_back(current);
            indices.push_back(next);
            indices.push_back(currentNext);

            // Triangle 2
            indices.push_back(currentNext);
            indices.push_back(next);
            indices.push_back(nextNext);
        }
    }

    return {vertices, indices};
}


