#include "Texture.hpp"
#include "Errors.hpp"
#include "stb_image.h"
#include <cassert>
#include <iostream>

Texture::Texture()
{
}

Texture::~Texture()
{
	//Deleting the texture based on number and address
	glDeleteTextures(1, &_textureHandler);
}

void Texture::init(const string& fileName)
{
	/*An int which holds the width, height and number of
	components of the image*/
	int width, height, imageComponents;
	//Loading the image and storing the data using the stbi_loadydoodah
	unsigned char* imageData = stbi_load((fileName).c_str(), &width, &height, &imageComponents, 4);
	//A little bit of error checking
	if (imageData == NULL)
	{
		fatalError("Texture " + fileName + "could not be loaded!");
	}
	//Generating the texture by number and the address of the texture in memory
	glGenTextures(1, &_textureHandler);
	//Telling OpenGL the texture is 2D and binding it
	glBindTexture(GL_TEXTURE_2D, _textureHandler);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//Linear filtering incase the texture is smaller than the area it is being bound to
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
	//Linear filtering incase the texture is bigger than the area it is being bound to
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

	stbi_image_free(imageData);
}

void Texture::bindTexture(GLuint unit)
{
	//Just checking that we're using one of 32 textures
	assert(unit >= 0 && unit <= 31); 
	//Setting the active texture
	glActiveTexture(GL_TEXTURE0 + unit);
	//The type of texture and a final binding!
	glBindTexture(GL_TEXTURE_2D, _textureHandler);
}


