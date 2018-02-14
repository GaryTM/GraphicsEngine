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
	colour = vec4 (fragmentColour.r * (cos(fragmentPosition.x * 2.0 + time) + 1.0) * 0.5,
					fragmentColour.g * (cos(fragmentPosition.y * 4.0 + time) + 1.0) * 0.5,
					fragmentColour.b * (cos(fragmentPosition.x * 1.5 + time) + 1.0) * 0.5, fragmentColour.a);
}