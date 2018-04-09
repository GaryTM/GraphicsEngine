#version 400

in vec3 fragmentPosition;

//Outputting the RGBA colour
out vec4 colour;

//Uniform variables are global across an entire mesh meaning data is not passed per vertex
//Cutting down that computation, yo!
uniform float time;

void main()
{
	colour = vec4 ((cos(fragmentPosition.x * 1000.0 + time) + 1.0) * 0.5,
					(sin(fragmentPosition.y * 1000 + time) + 1.0) * 0.5,
					(sin(fragmentPosition.z * 1000.0 + time) + 1.0) * 0.5, 1.0);
}