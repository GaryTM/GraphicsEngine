#pragma once

#include<GL\glew.h>
//The Vertex struct is used purely to hold data
struct Vertex
{
	/*A struct of type position to handle the position of vertices.
	Storing a struct or class within another of the same type is called composition*/
	struct Position
	{
		float x;
		float y;
	}
	/*Adding this lower case position outside the body of the struct
	but before the semi-colon creates an instance of the struct meaning
	something.position.x/y will be a valid call*/
	position;

	//The colour struct uses the exact same principles as struct Position
	struct Colour
	{
		/*Using GLubyte here guarantees that each colour and the alpha will
		only be one byte and since there is four it will align correctly*/
		GLubyte r;
		GLubyte g;
		GLubyte b;
		GLubyte a;
	}
	colour;

	
	//*********************************** GOOD TO REMEMBER ***********************************

	/*Adding this additional byte of padding would mean the Vertex struct would be
	a multiple of four bytes if the colour array was only storing 3 values
	(float(2) = 8 + colour[3] = 3 + padding = 1 = 12 in total) which is important for alignment*/
	
	//GLubyte padding;
};
