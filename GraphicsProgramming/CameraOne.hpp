#pragma once
#include "Camera.hpp"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

struct CameraOne : public Camera
{
public:
	CameraOne()
	{
	}
	void update(const Model &_fire, Window &_gameWindow, Input &_input)
	{
			if (_input.wasDown(SDLK_RETURN))
			{
				initCamera(vec3(_fire.transform.GetPosition().x, _fire.transform.GetPosition().y, _fire.transform.GetPosition().z - 5.0f), 70.f, (float)_gameWindow.getWidth() / _gameWindow.getHeight(), 0.01f, 1000.0f);
			}
			if (_input.wasDown(SDLK_BACKSPACE))
			{
				initCamera(vec3(_fire.transform.GetPosition().x, _fire.transform.GetPosition().y, _fire.transform.GetPosition().z - 10.0f), 70.f, (float)_gameWindow.getWidth() / _gameWindow.getHeight(), 0.01f, 1000.0f);
			}
			if (_input.wasDown(SDLK_KP_8))
			{
				initCamera(vec3(_fire.transform.GetPosition().x, _fire.transform.GetPosition().y + 2.0f, _fire.transform.GetPosition().z - 5.0f), 70.f, (float)_gameWindow.getWidth() / _gameWindow.getHeight(), 0.01f, 1000.0f);
				Pitch(0.45f);
			}
			if (_input.wasDown(SDLK_KP_2))
			{
				initCamera(vec3(_fire.transform.GetPosition().x, _fire.transform.GetPosition().y - 2.0f, _fire.transform.GetPosition().z - 5.0f), 70.f, (float)_gameWindow.getWidth() / _gameWindow.getHeight(), 0.01f, 1000.0f);
				Pitch(-0.45f);
			}
			if (_input.wasDown(SDLK_KP_4))
			{
				initCamera(vec3(_fire.transform.GetPosition().x + 2.0f, _fire.transform.GetPosition().y, _fire.transform.GetPosition().z - 5.0f), 70.f, (float)_gameWindow.getWidth() / _gameWindow.getHeight(), 0.01f, 1000.0f);
				RotateY(-0.45f);
			}
			if (_input.wasDown(SDLK_KP_6))
			{
				initCamera(vec3(_fire.transform.GetPosition().x - 2.0f, _fire.transform.GetPosition().y, _fire.transform.GetPosition().z - 5.0f), 70.f, (float)_gameWindow.getWidth() / _gameWindow.getHeight(), 0.01f, 1000.0f);
				RotateY(0.45f);
			}
			/*if (_input.isButDown(SDL_BUTTON_RIGHT) && SDL_MOUSEMOTION)
			{
			_mainCamera.initCamera(vec3(_model.transform.GetPosition()->x - 2.0f, _model.transform.GetPosition()->y, _model.transform.GetPosition()->z - 5.0f), 70.f, (float)_gameWindow.getWidth() / _gameWindow.getHeight(), 0.01f, 1000.0f);
			}*/
	}
};