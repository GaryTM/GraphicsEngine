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
	_time(0.0f)
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

	_woodDoor.loadModel("Models/WoodDoor.obj");
	_barrel.loadModel("Models/Barrel.obj");
	_wallTop.loadModel("Models/WallTop.obj");
	_wallBottom.loadModel("Models/WallBottom.obj");

	_woodDoorTexture.init("Textures/WoodDoorTexture.jpg");
	_barrelTexture.init("Textures/BarrelTexture.jpg");
	_wallTexture.init("Textures/WallTexture.jpg");

	_cameraOne.initCamera(vec3(0.0f, 1.0f, -3.5f), 70.f, (float)_gameWindow.getWidth() / _gameWindow.getHeight(), 0.01f, 1000.0f);
	_cameraOne.Pitch(0.35f);
	_ticker = 0.75f;
	//Initialising all shaders
	initShaders();
}

void MainGame::initShaders()
{
	//Compiling the vertex and fragment shader from file
	_funkyColour.compileShaders("Shaders/FunkyColour.vert", "Shaders/FunkyColour.frag");
	_solidColour.compileShaders("Shaders/SolidColour.vert", "Shaders/SolidColour.frag");
	_textured.compileShaders("Shaders/Textured.vert", "Shaders/Textured.frag");
	//Adding the attributes
	_funkyColour.createAttribute("vertexPosition");
	_funkyColour.createAttribute("vertexColour");

	//Linking the shaders
	_funkyColour.linkShaders();
	_solidColour.linkShaders();
	_textured.linkShaders();
}
void MainGame::gameLoop()
{
	//Setting what should happen while the program is running
	while (_currentGameState != GameState::EXIT)
	{
		processInput();
		_time += 0.1f;
		_cameraOne.update(_wallBottom, _gameWindow, _input);
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
	_gameWindow.clearWindow(1.0f, 1.0f, 1.0f, 1.0f);

	//_sprite.draw();

	float _sinCounter = sinf(_ticker);
	float _absSinCounter = abs(_sinCounter);

	//Setting the uniform before drawing
	GLuint timeLocation = _funkyColour.getUniformLocation("time");
	//Sending the variable (1f symbolises there is 1 Float)
	glUniform1f(timeLocation, _time);

	CreateTheModels();

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

void MainGame::CreateTheModels()
{
	//Draw the wooden door
	_woodDoor.transform.SetPosition(vec3(-0.5f, -1.0f, 0.0f));
	_woodDoor.transform.SetRotation(vec3(0.0f, 0.0f, 0.0f));
	_woodDoor.transform.SetScale(vec3(1.0f, 1.0f, 1.0f));
	_woodDoor.updateCollisionSphere(_woodDoor.transform.GetPosition(), 0.50f);
	_woodDoor.draw(_cameraOne, &_textured, &_woodDoorTexture);

	//Draw the barrel
	_barrel.transform.SetPosition(vec3(-1.2f, -1.0f, 0.0f));
	_barrel.transform.SetRotation(vec3(0.0f, 0.0f, 0.0f));
	_barrel.transform.SetScale(vec3(1.0f, 1.0f, 1.0f));
	_barrel.updateCollisionSphere(_barrel.transform.GetPosition(), 0.50f);
	_barrel.draw(_cameraOne, &_textured, &_barrelTexture);

	//Draw the top of the wall
	_wallTop.transform.SetPosition(vec3(-0.5f, 0.0f, 0.0f));
	_wallTop.transform.SetRotation(vec3(0.0f, 0.0f, 0.0f));
	_wallTop.transform.SetScale(vec3(1.0f, 1.0f, 1.0f));
	_wallTop.updateCollisionSphere(_wallTop.transform.GetPosition(), 0.50f);
	_wallTop.draw(_cameraOne, &_solidColour, &_wallTexture);
	//... and the bottom
	_wallBottom.transform.SetPosition(vec3(-0.5f, -1.0f, 0.0f));
	_wallBottom.transform.SetRotation(vec3(0.0f, 0.0f, 0.0f));
	_wallBottom.transform.SetScale(vec3(1.0f, 1.0f, 1.0f));
	_wallBottom.updateCollisionSphere(_wallBottom.transform.GetPosition(), 0.50f);
	_wallBottom.draw(_cameraOne, &_solidColour, &_wallTexture);
	//and again
	_wallBottom.transform.SetPosition(vec3(-0.5f, 0.15f, 0.0f));
	_wallBottom.transform.SetRotation(vec3(0.0f, 0.0f, 0.0f));
	_wallBottom.transform.SetScale(vec3(1.0f, 1.0f, 1.0f));
	_wallBottom.updateCollisionSphere(_wallBottom.transform.GetPosition(), 0.50f);
	_wallBottom.draw(_cameraOne, &_solidColour, &_wallTexture);
}


