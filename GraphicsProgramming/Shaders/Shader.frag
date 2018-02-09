#version 130

//Inputting the fragment colour from the vertex shader
in vec4 fragmentColour;

//Outputting the RGB colour
out vec4 colour;

void main()
{
	colour = fragmentColour;
}