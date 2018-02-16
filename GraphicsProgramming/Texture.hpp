#pragma once
#include <GL\glew.h>

#include <string>

using namespace std;

class Texture
{
public:
	Texture();
	~Texture();
	void init(const string& fileName);
	void bindTexture(GLuint unit);
	//A setter to get the texure handler
	void setTextureHandler(const GLuint& _textureHandler)
	{
		this->_textureHandler = _textureHandler;
	}
	//And the getter too!
	GLuint getTextureHandler()
	{
		return this->_textureHandler;
	}
private:
	GLuint _textureHandler;
};

