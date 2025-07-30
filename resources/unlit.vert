#version 330 core 
layout(location = 0) in vec3 aPos;

void main()
{
	// Set the position of the vertex
	gl_Position = vec4(aPos, 1.0);
	
	
}