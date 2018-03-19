#version 120

varying vec3 texCoord0;

uniform sampler2D diffuse;

void main()
{
	gl_FragColor = texture2D(diffuse, texCoord0);
}
