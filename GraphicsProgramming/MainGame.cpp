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
	//Models
	_sofa.loadModel("Models/sofa.obj");
	_singleSofa.loadModel("Models/sofa_single.obj");
	_foldTable.loadModel("Models/table_fold.obj");

	//Textures
	_woodDoorTexture.init("Textures/WoodDoorTexture.jpg");
	_barrelTexture.init("Textures/BarrelTexture.jpg");
	_wallTexture.init("Textures/WallTexture.jpg");

	_cameraOne.initCamera(vec3(0.0f, 1.25f, -3.0f), 70.f, (float)_gameWindow.getWidth() / _gameWindow.getHeight(), 0.01f, 1000.0f);
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
	_toon.compileShaders("Shaders/Toon.vert", "Shaders/Toon.frag");
	_blur.compileShaders("Shaders/Blur.vert", "Shaders/Blur.frag");
	//Adding the attributes
	_funkyColour.createAttribute("vertexPosition");
	_funkyColour.createAttribute("vertexColour");

	//Linking the shaders
	_funkyColour.linkShaders();
	_solidColour.linkShaders();
	_textured.linkShaders();
	_toon.linkShaders();
	_blur.linkShaders();
}
void MainGame::gameLoop()
{
	//Setting what should happen while the program is running
	while (_currentGameState != GameState::EXIT)
	{
		processInput();
		_time += 0.1f;
		_cameraOne.update(_sofa, _gameWindow, _input);
		draw();
	}
}
//This is how collisions between two models is checked and allows for lots of funk (sounds to play etc.)
bool MainGame::collision(vec3 model1Position, float model1Radius, vec3 model2Position, float model2Radius)
{
	float distance = sqrt((model2Position.x - model1Position.x)*(model2Position.x - model1Position.x) + (model2Position.y - model1Position.y)*(model2Position.y - model1Position.y) + (model2Position.z - model1Position.z)*(model2Position.z - model1Position.z));

	if (distance < (model1Radius + model2Radius))
	{
		_audioDevice.setListener(_cameraOne.GetPosition(), model1Position);
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
}

void MainGame::CreateTheModels()
{
	//Draw the sofa
	_sofa.transform.SetPosition(vec3(0.0f, 0.0f, 0.0f));
	_sofa.transform.SetRotation(vec3(0.0f, 0.0f, 0.0f));
	_sofa.transform.SetScale(vec3(1.0f, 1.0f, 1.0f));
	setToonLighting();
	_sofa.updateCollisionSphere(_sofa.transform.GetPosition(), 0.50f);
	_sofa.draw(_cameraOne, &_toon, &_barrelTexture);

	//Draw the foldable table
	_foldTable.transform.SetPosition(vec3(0.25f, 0.0f, -1.0f));
	_foldTable.transform.SetRotation(vec3(0.0f, 0.0f, 0.0f));
	_foldTable.transform.SetScale(vec3(1.0f, 1.0f, 1.0f));
	setToonLighting();
	_foldTable.updateCollisionSphere(_foldTable.transform.GetPosition(), 0.50f);
	_foldTable.draw(_cameraOne, &_toon, &_barrelTexture);

	//Draw the single sofa
	_singleSofa.transform.SetPosition(vec3(-1.5f, 0.0f, 0.0f));
	_singleSofa.transform.SetRotation(vec3(0.0f, 0.0f, 0.0f));
	_singleSofa.transform.SetScale(vec3(1.0f, 1.0f, 1.0f));
	setToonLighting();
	_singleSofa.updateCollisionSphere(_singleSofa.transform.GetPosition(), 0.50f);
	_singleSofa.draw(_cameraOne, &_toon, &_barrelTexture);
}
void MainGame::setToonLighting()
{
	_toon.setVec3("lightDir", vec3(1.0f, 1.0f, 1.0f));
}

void MainGame::setADSLighting()
{
	_modelView = transform.GetModel() * _cameraOne.GetView();

	_toon.setMat4("ModelViewMatrix", _modelView);
	_toon.setMat4("ProjectionMatrix", _cameraOne.GetProjection());

	mat4 normalMatrix = transpose(inverse(_modelView));

	_toon.setMat4("NormalMatrix", normalMatrix);

	_toon.setVec4("Position", vec4(10.0, 10.0, 10.0, 1.0));
	_toon.setVec3("Intensity", vec3(10.0, 10.0, 10.0));

	_toon.setVec3("ka", vec3(0.5, 0.5, 0.5));
	_toon.setVec3("kd", vec3(0.5, 0.5, 0.5));
	_toon.setVec3("ks", vec3(0.5, 0.5, 0.5));

	_toon.setFloat("Shininess", 0.5);
}

/********************************** IMMEDIATE MODE. GOOD TO KNOW, BUT SHOULD BE AVOIDED **********************************

glEnableClientState(GL_COLOR_ARRAY);
//Tells OpenGL which type of polygon should be drawn (triangles, points etc.)
glBegin(GL_TRIANGLES);

glColor3f(1.0f, 0.5f, 0.5f);
glVertex2f(0, 0);
glVertex2f(0, 1);
glVertex2f(1, 1);

glEnd();*/

