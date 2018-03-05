#version 130

//Inputting the fragment colour from the vertex shader
in vec4 fragmentColour;

in vec3 fragmentPosition;

//Outputting the RGB colour
out vec4 colour;

//Uniform variables are global across an entire mesh meaning data is not passed per vertex
//Cutting down that computation, yo!
uniform float time;

void main()
{
	colour = vec4 (fragmentColour.r * 5, fragmentColour.g, fragmentColour.b,  fragmentColour.a);
}