#include <iostream>
#include "Shader.hpp"
#include "Errors.hpp"

#include <vector>
#include <fstream>

using namespace std;

/*These privates variables are being initialised using an inistialisation list
which only works for constructors, but is faster than adding 
_numAttributes = 0; etc. to the body of the constructor. REMEMBER THIS!*/
Shader::Shader() :
	_numAttributes(0),
	_shaderProgram(0),
	_vertShader(0),
	_fragShader(0)
{
}

Shader::~Shader()
{
}

void Shader::shaderCompiler(const string& vertShaderPath, const string& fragShaderPath)
{
	//Creating a new program and assigning it to program id
	_shaderProgram = glCreateProgram();

	//Specifies that _vertShaderID is a GL_VERTEX_SHADER
	_vertShader = glCreateShader(GL_VERTEX_SHADER);
	if (_vertShader == 0)
	{
		fatalError("Vertex shader could not be created!");
	}

	//Specifies that _fragShaderID is a GL_FRAGMENT_SHADER
	_fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	if (_fragShader == 0)
	{
		fatalError("Fragment shader could not be created!");
	}
	compileShader(vertShaderPath, _vertShader);
	compileShader(fragShaderPath, _fragShader);
}
void Shader::shaderLinker()
{
	//Attaching the shaders to the program just created
	glAttachShader(_shaderProgram, _vertShader);
	glAttachShader(_shaderProgram, _fragShader);

	//Linking the program
	glLinkProgram(_shaderProgram);

	GLint isLinked = 0;
	//Checking the program is linked using GL_LINK_STATUS and throwing errors where neccessary
	glGetProgramiv(_shaderProgram, GL_LINK_STATUS, &isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(_shaderProgram, GL_INFO_LOG_LENGTH, &maxLength);

		vector<char> errorLog(maxLength);
		glGetProgramInfoLog(_shaderProgram, maxLength, &maxLength, &errorLog[0]);

		//Deleting the program when it is no longer required
		glDeleteProgram(_shaderProgram);
		//Deleting the shaders when they are no longer required (freeing up resources, yo!)
		glDeleteShader(_vertShader);
		glDeleteShader(_fragShader);

		printf("%s\n", &errorLog[0]);
		fatalError("Could not link shaders!");
	}

	//Ensuring the shaders are detached
	glDetachShader(_shaderProgram, _vertShader);
	glDetachShader(_shaderProgram, _fragShader);
}

void Shader::createAttribute(const string& attributeName)
{
	glBindAttribLocation(_shaderProgram, _numAttributes++, attributeName.c_str());
}

void Shader::bindShader()
{
	glUseProgram(_shaderProgram);
	//Loops through the attributes and enables the ones that are bound
	for (int i = 0; i < _numAttributes; i++)
	{
		//These must be enabled or the shader will not be able to use them
		glEnableVertexAttribArray(i);
	}
}
void Shader::unbindShader()
{
	//Setting this to 0 will unbind the program
	glUseProgram(0);

	for (int i = 0; i < _numAttributes; i++)
	{
		glDisableVertexAttribArray(i);
	}
}


//Gets the location of the uniform with some error checking to avoid invalidity
GLint Shader::getUniformLocation(const string uniformName)
{
	GLint uniformLocation = glGetUniformLocation(_shaderProgram, uniformName.c_str());

	if (uniformLocation == GL_INVALID_INDEX)
	{
		fatalError("Uniform " + uniformName + " is invalid!");
	}
	return uniformLocation;
}

void Shader::compileShader(const string& shaderFilePath, GLuint id)
{
	//Loading the code from the shader files using an ifstream
	ifstream vertexFile(shaderFilePath);
	//Checking if the vertex file fails to load and throwing two error messages
	if (vertexFile.fail())
	{
		perror(shaderFilePath.c_str());
		fatalError("Unable to open " + shaderFilePath);
	}

	string fileContents = "";
	string line;

	/*This loop takes all of the information from the shader file
	and passes it into the string named line.
	The getline function only returns true when there is a readable line*/
	while (getline(vertexFile, line))
	{
		//Combining the strings then adding a new line
		fileContents += line + "\n";
	}
	vertexFile.close();

	const char* fileContentsPtr = fileContents.c_str();
	/*This changes the source code in the shader to the source
	code which was passed into the array of strings, line*/
	glShaderSource(id, 1, &fileContentsPtr, nullptr);
	//Compiles the array of strings, line
	glCompileShader(id);

	GLint isCompiled = 0;
	//Checking the status of compilation with regards to the vertex shader
	glGetShaderiv(id, GL_COMPILE_STATUS, &isCompiled);

	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		/*This will get the length of the log OpenGL creates when compiling
		which is where we get the maxLength value*/
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);
		//Essentially a string
		vector<char> errorLog(maxLength);
		//Takes the log OpenGL created when compiling and adds it to the errorLog
		glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

		glDeleteShader(id);
		/*This creates a string with a new line which is the address of
		first element in errorLog, printing the vector of chars as a string*/
		printf("%s\n", &errorLog[0]);
		fatalError("Could not compile shader " + shaderFilePath);
	}
}

