#version 130
//This shader operates on every vertex

//Telling OpenGL we have an input of the Vertex position on a per vertex basis
//This holds 2 floats for the x and y coordinates
in vec2 vertexPosition;
//This holds 4 floats for r,g,b,a
in vec4 vertexColour;

//This is being output to the fragment shader. It will be interpolated at this
//stage and then the fragment shader will use the mixed colour
out vec4 fragmentColour;

out vec2 fragmentPosition;

//The main program for the vertex shader
void main()
{
	//This tells the fragment shader the position of the vertex (vertexPosition)
	gl_Position.xy = vertexPosition;
	gl_Position.z = 0.0;
	
	//This indicates that all coordinates are normalised
	gl_Position.w = 1.0;
	
	//This sets the fragment colour to equal the vertex colour
	fragmentColour = vertexColour;

	fragmentPosition = vertexPosition;
}