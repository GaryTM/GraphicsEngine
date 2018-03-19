    #version 150 core

    in vec3 vertexPosition;
    in vec3 colour;
    in vec2 texture;

    out vec3 Colour;
    out vec2 Texture;

	//Transformation matrix received from camera
uniform mat4 transform;

    void main()
    {
        Colour = colour;
        Texture = texture;
		gl_Position = transform * vec4(vertexPosition, 1);
}