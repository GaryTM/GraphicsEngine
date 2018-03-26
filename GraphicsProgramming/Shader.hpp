#pragma once
#include<GL\glew.h>
#include <string>

#include "Camera.hpp"
#include "Transform.hpp"

using namespace std;
using namespace glm;
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

	// uniform functions
	// ------------------------------------------------------------------------
	void setBool(const string &name, bool value) const
	{
		glUniform1i(glGetUniformLocation(_shaderProgram, name.c_str()), (int)value);
	}
	// ------------------------------------------------------------------------
	void setInt(const string &name, int value) const
	{
		glUniform1i(glGetUniformLocation(_shaderProgram, name.c_str()), value);
	}
	// ------------------------------------------------------------------------
	void setFloat(const string &name, float value) const
	{
		glUniform1f(glGetUniformLocation(_shaderProgram, name.c_str()), value);
	}
	// ------------------------------------------------------------------------
	void setVec2(const string &name, const vec2 &value) const
	{
		glUniform2fv(glGetUniformLocation(_shaderProgram, name.c_str()), 1, &value[0]);
	}
	void setVec2(const string &name, float x, float y) const
	{
		glUniform2f(glGetUniformLocation(_shaderProgram, name.c_str()), x, y);
	}
	// ------------------------------------------------------------------------
	void setVec3(const string &name, const vec3 &value) const
	{
		glUniform3fv(glGetUniformLocation(_shaderProgram, name.c_str()), 1, &value[0]);
	}
	void setVec3(const string &name, float x, float y, float z) const
	{
		glUniform3f(glGetUniformLocation(_shaderProgram, name.c_str()), x, y, z);
	}
	// ------------------------------------------------------------------------
	void setVec4(const string &name, const vec4 &value) const
	{
		glUniform4fv(glGetUniformLocation(_shaderProgram, name.c_str()), 1, &value[0]);
	}
	void setVec4(const string &name, float x, float y, float z, float w)
	{
		glUniform4f(glGetUniformLocation(_shaderProgram, name.c_str()), x, y, z, w);
	}
	// ------------------------------------------------------------------------
	void setMat2(const string &name, const mat2 &mat) const
	{
		glUniformMatrix2fv(glGetUniformLocation(_shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
	// ------------------------------------------------------------------------
	void setMat3(const string &name, const mat3 &mat) const
	{
		glUniformMatrix3fv(glGetUniformLocation(_shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
	// ------------------------------------------------------------------------
	void setMat4(const string &name, const mat4 &mat) const
	{
		glUniformMatrix4fv(glGetUniformLocation(_shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
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

