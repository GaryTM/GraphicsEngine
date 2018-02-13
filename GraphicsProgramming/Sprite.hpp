#pragma once
#include <GL\glew.h>

//A struct of type position to handle the position of vertices.	
struct Position
{
	float x;
	float y;
};

//The colour struct uses the exact same principles as struct Position
struct Colour
{
	/*Using GLubyte here guarantees that each colour and the alpha will
	only be one byte and since there is four it will align correctly*/
	GLubyte r;
	GLubyte g;
	GLubyte b;
	GLubyte a;
};

//The Vertex struct is used purely to hold data
struct Vertex2D
{
	//An instance of the position struct
	Position position;
	//An instance of the colour struct
	Colour colour;


	//*********************************** GOOD TO REMEMBER ***********************************

	/*Adding this additional byte of padding would mean the Vertex struct would be
	a multiple of four bytes if the colour array was only storing 3 values
	(float(2) = 8 + colour[3] = 3 + padding = 1 = 12 in total) which is important for alignment*/

	//GLubyte padding;
};

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
	GLuint _spriteVertexBufferObject;
	GLuint _spriteVertexArrayObject;
	GLuint _spriteElementBufferObject;
};

