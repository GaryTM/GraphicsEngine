    #version 150 core

    in vec3 Colour;
    in vec2 Texture;
    out vec4 outColour;

    uniform sampler3D textures;

    void main()
    {
        outColour = texture(textures, Texture) * vec4(Colour, 1.0);
    }