#pragma once
#include<GL\glew.h>
#include <string>

#include "Camera.hpp"
#include "Transform.hpp"

using namespace std;
class Shader
{
public:
	Shader();
	~Shader();
	//Compiles the shaders from GLSL and makes them usable in OpenGL
	void compileShaders(const string& vertShaderPath, const string& fragShaderPath);
	//Links the shaders together into the program
	void linkShaders();
	//Used to bind attributes such as vertex positions and colours etc.
	void createAttribute(const string& attributeName);
	//Allows for a program to be bound
	void bindShader();
	//Allows for a program to be unbound... wow!
	void unbindShader();

	GLint getUniformLocation(const string uniformName);
private:
	//Stores how many attributes the program currently has
	int _numAttributes;
	//A generic way to compile multiple types of shaders
	void compileShader(const string& shaderFilePath, GLuint id);
	//This stores the final shader program
	GLuint _shaderProgram;
	//This stores the vertex shader
	GLuint _vertShader;
	//This stores the fragment shader
	GLuint _fragShader;
};

