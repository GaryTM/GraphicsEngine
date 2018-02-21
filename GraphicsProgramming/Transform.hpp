#pragma once

#include "Camera.hpp"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

using namespace glm;

struct Transform
{
public:
	Transform(const vec3& position = vec3(), const vec3& rotation = vec3(), const vec3& scale = vec3(1.0f, 1.0f, 1.0f))
	{
		this->_position = position;
		this->_rotation = rotation;
		this->_scale = scale;
	}
	//A 4x4 matrix full of 4x4 matrices which allows the model to be called
	inline mat4 GetModel() const
	{
		mat4 positionMatrix = translate(_position);
		mat4 scaleMatrix = scale(_scale);
		mat4 rotateX = rotate(_rotation.x, vec3(1.0, 0.0, 0.0));
		mat4 rotateY = rotate(_rotation.y, vec3(0.0, 1.0, 0.0));
		mat4 rotateZ = rotate(_rotation.z, vec3(0.0, 0.0, 1.0));
		mat4 rotateMatrix = rotateX * rotateY * rotateZ;

		return positionMatrix * rotateMatrix * scaleMatrix;
	}

	//Getters for the position, rotation and scale of the matrix
	inline vec3 GetPosition() { return _position; } 
	inline vec3* GetRotation() { return &_rotation; }
	inline vec3* GetScale() { return &_scale; }
	//Setters for the position, rotation and scale of the matrix
	inline void SetPosition(const vec3 position) { this->_position = position; }
	inline void SetRotation(const vec3& rotation) { this->_rotation = rotation; }
	inline void SetScale(const vec3& scale) { this->_scale = scale; }

private:
	vec3 _position;
	vec3 _rotation;
	vec3 _scale;
};