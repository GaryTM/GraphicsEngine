#pragma once
#include <GL\glew.h>
class Sprite
{
public:
	Sprite();
	~Sprite();

	//Initialises the sprite with coordinates and size
	void init(float x, float y, float  width, float height);
	//Used to draw the Sprites!
	void draw();

private:
	int _x;
	int _y;
	int _width;
	int _height;
	/*An ID to store the vertex buffer object
	Using GLuint as opposed to unsigned int guarantees the VBO will be 32 bit*/
	GLuint _vertexBufferObject;
	GLuint _vertexArrayObject;
	GLuint _elementBufferObject;
};

