#version 400
//This shader operates on every vertex

//Telling OpenGL we have an input of the Vertex position on a per vertex basis
//This holds 3 floats for the x, y  and z coordinates
layout (location = 0) in vec3 vertexPosition;

//Transformation matrix received from camera
uniform mat4 transform;

out vec3 fragmentPosition;

//The main program for the vertex shader
void main()
{
	//This tells the fragment shader the position of the vertex (vertexPosition)
	gl_Position = transform * vec4(vertexPosition, 1);

	fragmentPosition = vertexPosition;
}