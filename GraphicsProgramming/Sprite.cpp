#include <iostream>
#include<cstddef>

#include "Sprite.hpp"

using namespace std;

Sprite::Sprite() :
	_spriteVertexBufferObject(0)
{
	  
}

Sprite::~Sprite()
{
	if (_spriteVertexBufferObject != 0)
	{
		glDeleteBuffers(1, &_spriteVertexBufferObject);
	}
}

void Sprite::init(float x, float y, float  width, float height)
{
	_x = x;
	_y = y;
	_width = width;  
	_height = height;

	//Only generating the Vertex Buffer Object if it hasn't already been generated
	if (_spriteVertexBufferObject == 0)
	{
		//Creating a Vertex Buffer Object and assigning it to _vertexBufferObject
		glGenBuffers(1, &_spriteVertexBufferObject);
		glGenBuffers(1, &_spriteElementBufferObject);
	}
	if (_spriteVertexArrayObject == 0)
	{
		glGenVertexArrays(1, &_spriteVertexArrayObject);
		glBindVertexArray(_spriteVertexArrayObject);
	}
	
	/*An array to store the vertex data. It holds 6 vertices
	and each vertex requires 2 floats for the x and y coordinate values*/
	Vertex2D vertexData[6];

	vertexData[0].position.x = x + width;
	vertexData[0].position.y = y + height;

	vertexData[1].position.x = x;
	vertexData[1].position.y = y + height;

	vertexData[2].position.x = x;
	vertexData[2].position.y = y;

	vertexData[3].position.x = x + width;
	vertexData[3].position.y = y;

	for (int i = 0; i < 6; i++)
	{
		vertexData[i].colour.r = 255;
		vertexData[i].colour.g = 255;
		vertexData[i].colour.b = 155;
		vertexData[i].colour.a = 255;
	}

	//Top left vertice
	vertexData[1].colour.r = 0;
	vertexData[1].colour.g = 255;
	vertexData[1].colour.b = 0;
	vertexData[1].colour.a = 255;

	//Bottom right vertice
	vertexData[3].colour.r = 255;
	vertexData[3].colour.g = 0;
	vertexData[3].colour.b = 0;
	vertexData[3].colour.a = 255;

	/*Indexing using an elements array allows the vertexData array to be cut 
	in half meaning less information has to be processed, meaning the CPU/GPU is happier!*/
	GLuint elements[] =
	{
		0, 1, 2,
		2, 3, 0
	};

	//********VBO********
	//Binds the buffer
	glBindBuffer(GL_ARRAY_BUFFER, _spriteVertexBufferObject);
	//Sends the buffer information
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

	//Unbinding the buffer (Not neccessary when using a VAO as the VAO takes the buffers when it is unbound
	//glBindBuffer(GL_ARRAY_BUFFER, 0);

	//********EBO********
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _spriteElementBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);

	/*Pointing OpenGL to the start of the data to be used
	This one in particular is used for the position
	The final parameter is 0 because in the Vertex struct
	position has nothing before it. Using offsetof means that
	if the value/position ever changes it won't need to be changed here
	It's for accuracy, yo!*/
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (void*)offsetof(Vertex2D, position));
	//Same as above for the colour
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex2D), (void*)offsetof(Vertex2D, colour));
	//glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Sprite::draw()
{
	glDisable(GL_CULL_FACE);

	//Tells OpenGL this is the current active buffer
	glBindBuffer(GL_ARRAY_BUFFER, _spriteVertexBufferObject);
	
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
