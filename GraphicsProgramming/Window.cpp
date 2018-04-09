#include "Window.hpp"

Window::Window() :
	_gameWindow(nullptr),
	_screenWidth(1280.0f),
	_screenHeight(720.0f)
{
}
Window::~Window()
{
	SDL_GL_DeleteContext(_glContext); // delete context
	SDL_DestroyWindow(_gameWindow); // detete window (make sure to delete the context and the window in the opposite order of creation in initDisplay())
	SDL_Quit();
}

float Window::getWidth() { return _screenWidth; } //getters
float Window::getHeight() { return _screenHeight; }

void Window::swapBuffer()
{
	/*Clears everything that has been drawn to the screen and switches
	to the windows via double buffering*/
	SDL_GL_SwapWindow(_gameWindow);
}

void Window::clearWindow(float r, float g, float b, float a)
{
	glClearColor(0.0f, 0.5f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear colour and depth buffer - set colour to colour defined in glClearColor
}

void Window::initWindow()
{
	//Initialises everything SDL has to offer!
	SDL_Init(SDL_INIT_EVERYTHING);

	glEnable(GL_DEPTH_TEST); //enable z-buffering 
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	/*Sets up the window giving it a title and ensuring it is centered on the x and y axis,
	screen width and height are then passed in and the final "flags" parameter grants the
	ability to specify how the window should initialise (fullscreen, windowed etc.)*/
	_gameWindow = SDL_CreateWindow
	("Gary Mulhall | Graphics Programming", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight, SDL_WINDOW_OPENGL);
	//Checks if the window failed to load and making it clear
	if (_gameWindow == nullptr)
	{
		fatalError("The window could not be created..");
	}
	//Creates OpenGL context which stores all OpenGl related context inluding VBOs, textures etc.
	 _glContext = SDL_GL_CreateContext(_gameWindow);

	if (_glContext == nullptr)
	{
		fatalError("SDL_GLContext failed to create..");
	}

	//Checks for errors when initialising GLEW
	GLenum error = glewInit();

	if (error != GLEW_OK)
	{
		fatalError("GLEW could not be initialised..");
	}
	/*Enables double buffering by creating a virtual window which
	is drawn to while the other clears and swaps between*/
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	//Sets the background colour
	glClearColor(0.4f, 1.0f, 1.0f, 1.0f);
}