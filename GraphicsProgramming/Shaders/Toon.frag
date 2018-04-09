uniform vec3 lightDir;
varying vec3 normal;

void main()
{
	float intensity;
	vec4 colour = vec4(1.0,0.0,0.0,1.0);;
	intensity = dot(lightDir,normal);

	if (intensity > 0.95)
		colour = vec4(1.0,0.5,0.5,1.0);
	else if (intensity > 0.5)
		colour = vec4(0.6,0.3,0.3,1.0);
	else if (intensity > 0.25)
		colour = vec4(0.4,0.2,0.2,1.0);
	else
		colour = vec4(0.2,0.1,0.1,1.0);
	gl_FragColor = colour;

}