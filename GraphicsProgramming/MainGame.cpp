#include <iostream>
#include <string>
#include "MainGame.hpp"
#include "Errors.hpp"

using namespace std;

MainGame::MainGame() : 
	_gameWindow(nullptr),
	_currentGameState(GameState::PLAY),
	_screenWidth(1280),
	_screenHeight(720),
	_time(0.0f)
{
}

MainGame::~MainGame()
{
}

void MainGame::run()
{
	initSystems();

	_sprite.init(-1.0f, -1.0f, 2.0f, 2.0f);

	gameLoop();
}

void MainGame::initSystems()
{
	//Initialises everything SDL has to offer!
	SDL_Init(SDL_INIT_EVERYTHING); 

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
	SDL_GLContext glContext = SDL_GL_CreateContext(_gameWindow);
	if (glContext == nullptr)
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

	initShaders();
}

void MainGame::initShaders()
{
	//Compiling the vertex and fragment shader from file
	_colourShader.shaderCompiler("Shaders/Shader.vert", "Shaders/Shader.frag");
	//Adding the attributes
	_colourShader.createAttribute("vertexPosition");
	_colourShader.createAttribute("vertexColour");
	//Linking the shaders
	_colourShader.shaderLinker();
}

void MainGame::gameLoop()
{
	//Setting what should happen while the program is running
	while (_currentGameState != GameState::EXIT)
	{
		processInput();
		_time += 0.001f;
		draw();
	}
}

void MainGame::processInput()
{
	//An instance of an event
	SDL_Event evnt;
	/*SDL_PollEvent checks which events need processed with the OS
	this can include inputs by the user*/
	//This loop only runs if there IS an event which needs to be processed
	while (SDL_PollEvent(&evnt))
	{
		//A switch statement used to check all the potential types of events
		switch (evnt.type)
		{
		case SDL_QUIT:
			//Exit the program if SDL_QUIT is called (the user closes the program)
			_currentGameState = GameState::EXIT;
			break;

		case SDL_MOUSEMOTION:
			cout << evnt.motion.x << " " << evnt.motion.y << endl;

			break;
		}
	}
}

void MainGame::draw()
{
	//Clears the entire depth buffer (I have no idea what difference the 1.0f value makes..
	glClearDepth(1.0f);
	//Clears the color buffer and the depth buffer every time the game is drawn
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_colourShader.bindShader();

	//Setting the uniform before drawing
	GLuint timeLocation = _colourShader.getUniformLocation("time");
	//Sending the variable (1f symbolises there is 1 Float)
	glUniform1f(timeLocation, _time);
	_sprite.draw();

	_colourShader.unbindShader();

	/*Clears everything that has been drawn to the screen and switches
	to the windows via double buffering*/
	SDL_GL_SwapWindow(_gameWindow);

	/********************************** IMMEDIATE MODE. GOOD TO KNOW, BUT SHOULD BE AVOIDED **********************************

	glEnableClientState(GL_COLOR_ARRAY);
	//Tells OpenGL which type of polygon should be drawn (triangles, points etc.)
	glBegin(GL_TRIANGLES);

	glColor3f(1.0f, 0.5f, 0.5f);
	glVertex2f(0, 0);
	glVertex2f(0, 1);
	glVertex2f(1, 1);

	glEnd();*/
}

