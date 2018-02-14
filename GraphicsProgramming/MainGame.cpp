#include <iostream>
#include <string>
#include "MainGame.hpp"
#include "Camera.hpp"
#include "Errors.hpp"

using namespace std;
using namespace glm;

Transform transform;

MainGame::MainGame() :
	_currentGameState(GameState::PLAY),
	_time(0.0f)
{
	Window* _gameWindow = new Window();
}

MainGame::~MainGame()
{
}

void MainGame::run()
{
	initSystems();

	//_sprite.init(-1.0f, -1.0f, 2.0f, 2.0f);

	gameLoop();
}

void MainGame::initSystems()
{
	_gameWindow.initWindow();

	_model.loadModel("Models/box.obj");
	
	_mainCamera.initCamera(vec3(0, 0, -10), 70.0f, (float)_gameWindow.getWidth() / _gameWindow.getHeight(), 0.01f, 1000.0f);

	_counter = 0.5f;

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
		if (_input.isDown(SDLK_RETURN))
		{
			_mainCamera.initCamera(vec3(_model.transform.GetPosition()->x, _model.transform.GetPosition()->y + 0.5f, _model.transform.GetPosition()->z - 1.5f), 70.f, (float)_gameWindow.getWidth() / _gameWindow.getHeight(), 0.01f, 1000.0f);
		}
		if (_input.isDown(SDLK_BACKSPACE))
		{
			_mainCamera.initCamera(vec3(0, 0, -10), 70.0f, (float)_gameWindow.getWidth() / _gameWindow.getHeight(), 0.01f, 1000.0f);
		}
		draw();
	}
}

bool MainGame::collision(vec3 model1Position, float model1Radius, vec3 model2Position, float model2Radius)
{
	float distance = sqrt((model2Position.x - model1Position.x)*(model2Position.x - model1Position.x) + (model2Position.y - model1Position.y)*(model2Position.y - model1Position.y) + (model2Position.z - model1Position.z)*(model2Position.z - model1Position.z));

	if (distance < (model1Radius + model2Radius))
	{
		_audioDevice.setListener(_mainCamera.getPosition(), model1Position);
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
			//cout << evnt.motion.x << " " << evnt.motion.y << endl;

			break;

		}
	}
	_input.EventHandler(eventList);
}

void MainGame::draw()
{
	_gameWindow.clearWindow(0.0f, 0.0f, 0.0f, 1.0f);

	float sinCounter = sinf(_counter);
	float absSinCounter = abs(sinCounter);

	//Setting the uniform before drawing
	GLuint timeLocation = _colourShader.getUniformLocation("time");
	//Sending the variable (1f symbolises there is 1 Float)
	glUniform1f(timeLocation, _time);
	//_sprite.draw();

	transform.SetPosition(vec3(sinf(_counter), -0.1, -5.0));
	transform.SetRotation(vec3(0.0, 0.0, 0.0));
	transform.SetScale(vec3(1.0, 1.0, 1.0));
	_colourShader.bindShader();

	_model.draw(_mainCamera, &_colourShader, transform);

	_colourShader.unbindShader();

	_counter = _counter + 0.01f;

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

