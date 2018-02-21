#version 130
//This shader operates on every vertex

//Telling OpenGL we have an input of the Vertex position on a per vertex basis
//This holds 3 floats for the x, y  and z coordinates
in vec3 vertexPosition;
//This holds 4 floats for r,g,b,a
in vec4 vertexColour;

//Transformation matrix received from camera
uniform mat4 transform;

//This is being output to the fragment shader. It will be interpolated at this
//stage and then the fragment shader will use the mixed colour
out vec4 fragmentColour;

out vec3 fragmentPosition;

//The main program for the vertex shader
void main()
{
	//This tells the fragment shader the position of the vertex (vertexPosition)
	gl_Position = transform * vec4(vertexPosition, 1);

	//This sets the fragment colour to equal the vertex colour
	fragmentColour = vertexColour;

	fragmentPosition = vertexPosition;
}