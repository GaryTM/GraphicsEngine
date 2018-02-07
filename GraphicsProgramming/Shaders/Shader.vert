#version 330
//This shader operates on every vertex

//Telling OpenGL we have an input of the Vertex position on a per vertex basis
//This holds 2 floats for the x and y coordinates
in vec2 vertexPos;

//The main program for the vertex shader
void main()
{
	//This tells the fragment shader the position of the vertex (vertexPos)
	gl_Position.xy = vertexPos;
	gl_Position.z = 0.0;
	
	//This indicates that all coordinates are normalised
	gl_Position.w = 1.0;
}