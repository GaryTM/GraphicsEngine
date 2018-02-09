#include <iostream>
#include<cstddef>

#include "Sprite.hpp"
#include "Vertex.hpp"

using namespace std;

Sprite::Sprite()
{
	GLuint _vertexBufferObject = 0;
}

Sprite::~Sprite()
{
	if (_vertexBufferObject != 0)
	{
		glDeleteBuffers(1, &_vertexBufferObject);
	}
}

void Sprite::init(float x, float y, float  width, float height)
{
	_x = x;
	_y = y;
	_width = width;  
	_height = height;

	//Only generating the Vertex Buffer Object if it hasn't already been generated
	if (_vertexBufferObject = 0)
	{
		//Creating a Vertex Buffer Object and assigning it to _vertexBufferObject
		glGenBuffers(1, &_vertexBufferObject);
	}
	/*An array to store the vertex data. It holds 6 vertices
	and each vertex requires 2 floats for the x and y coordinate values*/
	Vertex vertexData[6];

	vertexData[0].position.x = x + width;
	vertexData[0].position.y = y + height;

	vertexData[1].position.x = x;
	vertexData[1].position.y = y + height;

	vertexData[2].position.x = x;
	vertexData[2].position.y = y;

	vertexData[3].position.x = x;
	vertexData[3].position.y = y;

	vertexData[4].position.x = x + width;
	vertexData[4].position.y = y;

	vertexData[5].position.x = x + width;
	vertexData[5].position.y = y + height;

	for (int i = 0; i < 6; i++)
	{
		vertexData[i].colour.r = 255;
		vertexData[i].colour.g = 0;
		vertexData[i].colour.b = 255;
		vertexData[i].colour.a = 255;
	}

	//Binds the buffer
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferObject);
	//Sends the buffer information
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	//Unbinding the buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::draw()
{
	glDisable(GL_CULL_FACE);

	//Tells OpenGL this is the current active buffer
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferObject);
	glEnableVertexAttribArray(0);
	/*Pointing OpenGL to the start of the data to be used
	This one in particular is used for the position
	The final parameter is 0 because in the Vertex struct
	position has nothing before it. Using offsetof means that
	if the value/position ever changes it won't need to be changed here
	It's for accuracy, yo!*/
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	//Same as above for the colour
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, colour));
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
