#include <iostream>
#include "Sprite.hpp"

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

	float vertexData[12];

	vertexData[0] = x + width;
	vertexData[1] = y + height;
	vertexData[2] = x;
	vertexData[3] = y + height;
	vertexData[4] = x;
	vertexData[5] = y;

	vertexData[6] = x;
	vertexData[7] = y;
	vertexData[8] = x + width;
	vertexData[9] = y;
	vertexData[10] = x + width;
	vertexData[11] = y + height;

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
	//Pointing OpenGL to the start of the data to be used
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_TRUE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
