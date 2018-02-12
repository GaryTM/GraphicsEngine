#version 130

//Inputting the fragment colour from the vertex shader
in vec4 fragmentColour;

//Outputting the RGB colour
out vec4 colour;

//Uniform variables are global across an entire mesh meaning data is not passed per vertex
//Cutting down that computation, yo!
uniform float time;

void main()
{
	colour = fragmentColour + vec4 (1.0 * cos(time) + 1.0 * 0.5,
									1.0 * cos(time) + 2.0 * 0.5,
									1.0 * sin(time) + 1.0 * 0.5, 0.0);
}