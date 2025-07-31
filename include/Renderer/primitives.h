#pragma once
#include <Renderer/utils.h>
#include <vector>
#include <Renderer/mesh.h>
#include <glm/glm.hpp>

//3D primitive 


Primitive rectanglePrimitive = {

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

Primitive  trianglePrimitive = {
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
Primitive cubePrimitive = {
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


