#pragma once

#include "Transform.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "Input.hpp"

#include <glm\glm.hpp>
#include <GL\glew.h>
#include <string>
#include "obj_loader.h"

using namespace std;
using namespace glm;

struct Vertex3D
{
public:
	Vertex3D(const vec3& position, const vec2& textureCoordinate)
	{
		this->_position = position;
		this->_textureCoordinate = textureCoordinate;
		this->_normal = _normal;
	}
	//Getters for the position, texture coordinates and normals of the models
	vec3* GetPosition() { return &_position; }
	vec2* GetTextureCoords() { return &_textureCoordinate; }
	vec3* GetNormal() { return &_normal; }

private:
	vec3 _position;
	vec2 _textureCoordinate;
	vec3 _normal;
};

struct Sphere
{
public:
	//Required default constructor... ANNOYING!
	Sphere()
	{

	}
	Sphere(vec3& position, float radius)
	{
		this->_position = position;
	}

	vec3 GetSpherePosition() { return _position; }
	float GetSphereRadius() { return _radius; }
	//Setter for the collision sphere position
	void SetPosition(vec3 position)
	{
		this->_position = position;
	}
	//Setter for the collision sphere radius
	void SetRadius(float radius)
	{
		this->_radius = radius;
	}

private:
	vec3 _position;
	float _radius;
};

class Model
{
public:
	Model();
	~Model();

	Transform transform;
	Shader* _shader;

	void init(Vertex3D* vertices, unsigned int verticeCount, unsigned int* indices, unsigned int indiceCount);
	//Used to load a model from file
	void loadModel(const string& filename);
	//Used for initialising the model by making good use of the obj_loader
	void initModel(const IndexedModel& model);
	//Used to update the models collision sphere based on the models position and radius
	void updateCollisionSphere(vec3 position, float radius);
	//Getter for the sphere position
	vec3 getSpherePosition() { return _collisionSphere.GetSpherePosition(); }
	//Getter for the sphere radius
	float getSphereRadius() { return _collisionSphere.GetSphereRadius(); }
	void draw();
	void draw(const Camera& mainCamera, Shader* shader, Texture* texture);

private:
	/*An enum to return values based on position, texture coordinates etc.
	Copied over from Bryans code, might remove as not really neccessary..*/
	enum
	{
		VERTEX_BUFFER_POSITION,
		VERTEX_BUFFER_TEXTURECOORDINATE,
		VERTEX_BUFFER_NORMAL,
		VERTEX_BUFFER_INDEX,
		BUFFER_COUNT
	};

	//An instance of the sphere struct which will be used for model collision
	Sphere _collisionSphere;
	/*An ID to store the vertex buffer object
	Using GLuint as opposed to unsigned int guarantees the VBO will be 32 bit*/
	GLuint _vertexArrayObject;
	//Creating the array of buffers
	GLuint _vertexArrayBuffers[BUFFER_COUNT];
	//Limiter for how much of the VAO should be drawn
	unsigned int _drawCount;
};