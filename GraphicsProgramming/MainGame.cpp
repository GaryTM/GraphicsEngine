#include <iostream>
#include <string>
#include "MainGame.hpp"
#include "Errors.hpp"

using namespace std;
using namespace glm;

Transform transform;
/*These privates variables are being initialised using an inistialisation list
which only works for constructors, but is faster than adding
time = 0.0f; etc. to the body of the constructor. REMEMBER THIS!*/
MainGame::MainGame() :
	_currentGameState(GameState::PLAY),
	_time(0.0f),
	_cube(_input),
	_ball(_input)
{
	Window* _gameWindow = new Window();
}

MainGame::~MainGame()
{
}
//Run the game by initialising all the important stuff required 
void MainGame::run()
{
	initSystems();

	//_sprite.init(-1.0f, -1.0f, 1.0f, 1.0f);

	gameLoop();
}
//Initialise the required systems. Load the window, models, camera, shaders etc.
void MainGame::initSystems()
{
	_gameWindow.initWindow();

	_cube.loadModel("Models/box.obj");
	
	_ball.loadModel("Models/ball.obj");

	_tent.loadModel("Models/Tent.obj");

	_texture.init("Textures/Texture.jpg");

	_cameraOne.initCamera(vec3(2, 2, -12), 70.0f, (float)_gameWindow.getWidth() / _gameWindow.getHeight(), 0.01f, 1000.0f);
	_ticker = 0.5f;

initShaders();
}

void MainGame::initShaders()
{
	//Compiling the vertex and fragment shader from file
	_shader.compileShaders("Shaders/Shader.vert", "Shaders/Shader.frag");
	//Adding the attributes
	_shader.createAttribute("vertexPosition");
	_shader.createAttribute("vertexColour");

	//Linking the shaders
	_shader.linkShaders();
}

void MainGame::gameLoop()
{
	//Setting what should happen while the program is running
	while (_currentGameState != GameState::EXIT)
	{
		processInput();
		_time += 0.1f;
		_cameraOne.update(_cube, _gameWindow, _input);
		draw();
	}
}
//This is how collisions between two models is checked and allows for lots of funk (sounds to play etc.)
bool MainGame::collision(vec3 model1Position, float model1Radius, vec3 model2Position, float model2Radius)
{
	float distance = sqrt((model2Position.x - model1Position.x)*(model2Position.x - model1Position.x) + (model2Position.y - model1Position.y)*(model2Position.y - model1Position.y) + (model2Position.z - model1Position.z)*(model2Position.z - model1Position.z));

	if (distance < (model1Radius + model2Radius))
	{
		_audioDevice.setListener(_cameraOne.getPosition(), model1Position);
		//playAudio(whistle, m1Pos);
		return true;
	}
	else
	{
		return false;
	}
}
void MainGame::processInput()
{
	vector<SDL_Event> eventList;

	//An instance of an event
	SDL_Event evnt;
	/*SDL_PollEvent checks which events need processed with the OS
	this can include inputs by the user*/
	//This loop only runs if there IS an event which needs to be processed
	while (SDL_PollEvent(&evnt))
	{
		eventList.push_back(evnt);
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
	_input.EventHandler(eventList);
}

void MainGame::draw()
{
	_gameWindow.clearWindow(0.0f, 0.0f, 0.0f, 1.0f);

	//_sprite.draw();

	float _sinCounter = sinf(_ticker);
	float absSinCounter = abs(_sinCounter);

	//Setting the uniform before drawing
	GLuint timeLocation = _shader.getUniformLocation("time");
	//Sending the variable (1f symbolises there is 1 Float)
	glUniform1f(timeLocation, _time);

	////Draw the cube
	//_cube.transform.SetPosition(vec3(-3.0, 4.0, 0.0));
	//_cube.transform.SetRotation(vec3(0.0, 0.0, 0.0));
	//_cube.transform.SetScale(vec3(0.5, 0.5, 0.5));
	//_cube.update();
	//_cube.updateCollisionSphere(_cube.transform.GetPosition(), 0.50f);
	//_cube.draw(_cameraOne, &_shader, &_texture);

	////Draw the ball
	//_ball.transform.SetPosition(vec3(3.0, 4.0, 0.0));
	//_ball.transform.SetRotation(vec3(0.0, 0.0, 0.0));
	//_ball.transform.SetScale(vec3(0.5, 0.5, 0.5));
	////_ball.update();
	//_ball.updateCollisionSphere(_ball.transform.GetPosition(), 0.50f);
	//_ball.draw(_cameraOne, &_shader, &_texture);


	//Draw the tent
	_tent.transform.SetPosition(vec3(0.0, 0.0, 0.0));
	_tent.transform.SetRotation(vec3(0.0, 0.0, 0.0));
	_tent.transform.SetScale(vec3(1.0, 1.0, 1.0));
	_tent.updateCollisionSphere(_tent.transform.GetPosition(), 0.50f);
	_tent.draw(_cameraOne, &_shader, &_texture);

	_ticker = _ticker + 0.01f;

	_gameWindow.swapBuffer();

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


