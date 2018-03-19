#version 130

//This holds 3 floats for the x, y  and z coordinates
in vec3 vertexPosition;

out vec3 fragmentPosition;

//Transformation matrix received from camera
uniform mat4 transform;

void main()
{
	gl_Position = transform * vec4(vertexPosition, 1);
	fragmentPosition = vertexPosition;
}