#pragma once

#include <SDL/SDL.h>
#include <GL\glew.h>
#include <iostream>
#include <string>

#include "Errors.hpp"
using namespace std;


class Window
{
public:
	Window();
	~Window();
	void initWindow();
	void swapBuffer();
	void clearWindow(float r, float g, float b, float a);

	float getWidth();
	float getHeight();

private:

	SDL_GLContext _glContext; //global variable to hold the context
	SDL_Window* _gameWindow;
	float _screenWidth;
	float _screenHeight;
};
