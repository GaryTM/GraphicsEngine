#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

using namespace glm;

struct Camera
{
public:
	Camera()
	{
	}
	/*How the camera will be initialised using a position, field of view, screen aspect ratio
	and the near and far clipping planes*/
	void initCamera(const vec3& position, float fieldOfView, float aspectRatio, float nearClip, float farClip)
	{
		this->_position = position;
		this->_forward = vec3(0.0f, 0.0f, 1.0f);
		this->_up = vec3(0.0f, 1.0f, 0.0f);
		this->_projection = perspective(fieldOfView, aspectRatio, nearClip, farClip);
	}
	//A getter for the position of the camera
	vec3 getPosition()
	{
		return this->_position;
	}
	//A matrix which gets the view and projection for the camera
	inline mat4 GetViewProjection() const
	{
		return _projection *lookAt(_position, _position + _forward, _up);
	}
	//A function to move the camera forward
	void MoveForward(float amount)
	{
		_position += _forward * amount;
	}
	//A function to move the camera backward
	void MoveBackward(float amount)
	{
		_position -= _forward * amount;
	}
	//A function to move the camera right
	void MoveRight(float amount)
	{
		_position += cross(_up, _forward) * amount;
	}
	//A function to move the camera left
	void MoveLeft(float amount)
	{
		_position -= cross(_up, _forward) * amount;
	}
	//A function to control the pitch of the the camera
	void Pitch(float angle)
	{
		vec3 _right = normalize(cross(_up, _forward));
		_forward = vec3(normalize(rotate(angle, _right) * vec4(_forward, 0.0)));
		_up = normalize(cross(_forward, _right));
	}
	//A function allowing the camera to be rotated on the Y axis
	void RotateY(float angle)
	{
		static const vec3 UP(0.0f, 1.0f, 0.0f);

		mat4 _rotation = rotate(angle, UP);

		_forward = vec3(normalize(_rotation * vec4(_forward, 0.0)));
		_up = vec3(normalize(_rotation * vec4(_up, 0.0)));
	}
	//A function allowing the camera to be rotated on the X axis
	void RotateX(float angle)
	{
		static const vec3 FORWARD(0.0f, 0.0f, 1.0f);

		mat4 _rotation = rotate(angle, FORWARD);

		_forward = vec3(normalize(_rotation * vec4(_forward, 0.0)));
		_up = vec3(normalize(_rotation * vec4(_up, 0.0)));
	}
private:
	/*The projection matrix is used to map from the camera to the screen
	which is integral for the mvp matrix*/
	mat4 _projection;
	vec3 _position;
	vec3 _forward;
	vec3 _up;
};


