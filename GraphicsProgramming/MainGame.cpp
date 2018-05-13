#include <iostream>
#include <string>
#include "MainGame.hpp"
#include "Errors.hpp"

using namespace std;
using namespace glm;

Transform transform;
/*These private variables are being initialised using an inistialisation list
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
	_book.loadModel("Models/book.obj");

	//Textures
	_woodDoorTexture.init("Textures/WoodDoorTexture.jpg");
	_barrelTexture.init("Textures/BarrelTexture.jpg");
	_wallTexture.init("Textures/WallTexture.jpg");

	//setADSLighting();

	_cameraOne.initCamera(vec3(0.0f, 1.25f, -3.0f), 70.f, (float)_gameWindow.getWidth() / _gameWindow.getHeight(), 0.01f, 1000.0f);
	_cameraOne.Pitch(0.35f);
	_ticker = 0.75f;
	//Initialising all shaders
	initShaders();

	cout << "Use the num pad to move the camera around the 'book.'" << endl;
	cout << "Holding backspace slows the 'funky colour' effect." << endl;
	cout << "Far left has the blur shading (doesn't look as good as expected, but compiles and works.)" << endl;
	cout << "Next has the ADS lighting attached. Changing the intensity/position of the light changes the colour of the model." << endl;
	cout << "The small sofa is using the toon shader" << endl;
	cout << "The 'book' is using a bespoke shader which may cause seizures." << endl;
}

void MainGame::initShaders()
{
	//Compiling the vertex and fragment shader from file
	_funkyColour.compileShaders("Shaders/FunkyColour.vert", "Shaders/FunkyColour.frag");
	_solidColour.compileShaders("Shaders/SolidColour.vert", "Shaders/SolidColour.frag");
	_textured.compileShaders("Shaders/Textured.vert", "Shaders/Textured.frag");
	_toon.compileShaders("Shaders/Toon.vert", "Shaders/Toon.frag");
	_blur.compileShaders("Shaders/Blur.vert", "Shaders/Blur.frag");
	_ADS.compileShaders("Shaders/ADS.vert", "Shaders/ADS.frag");
	_rim.compileShaders("Shaders/Rim.vert", "Shaders/Rim.frag");
	//_fog.compileShaders("Shaders/Fog.vert", "Shaders/Fog.frag");

	//Linking the shaders
	_funkyColour.linkShaders();
	_solidColour.linkShaders();
	_textured.linkShaders();
	_toon.linkShaders();
	_blur.linkShaders();
	_ADS.linkShaders();
	_rim.linkShaders();
	//_fog.linkShaders();
}
void MainGame::gameLoop()
{
	//Setting what should happen while the program is running
	while (_currentGameState != GameState::EXIT)
	{
		processInput();
		_time += 0.1f;
		_cameraOne.update(_book, _gameWindow, _input);
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
		}
	}
	_input.EventHandler(eventList);
}

void MainGame::draw()
{
	_gameWindow.clearWindow(1.0f, 1.0f, 1.0f, 1.0f);

	float _sinCounter = sinf(_ticker);
	float _absSinCounter = abs(_sinCounter);

	CreateTheModels();
	_ticker = _ticker + 0.01f;

	_gameWindow.swapBuffer();
}

void MainGame::CreateTheModels()
{
	//Draw the sofa and apply the Phong lighting model to it along with the ADS shader
	_sofa.transform.SetPosition(vec3(0.0f, 0.0f, 0.0f));
	_sofa.transform.SetRotation(vec3(0.0f, 0.0f, 0.0f));
	_sofa.transform.SetScale(vec3(1.0f, 1.0f, 1.0f));
	setADSLighting();
	_sofa.updateCollisionSphere(_sofa.transform.GetPosition(), 0.50f);
	_sofa.draw(_cameraOne, &_ADS, &_barrelTexture);

	//Draw the foldable table and apply blur shader
	_foldTable.transform.SetPosition(vec3(2.0f, 0.0f, 0.0f));
	_foldTable.transform.SetRotation(vec3(0.0f, 0.0f, 0.0f));
	_foldTable.transform.SetScale(vec3(1.0f, 1.0f, 1.0f));
	setBlurLighting();
	_foldTable.updateCollisionSphere(_foldTable.transform.GetPosition(), 0.50f);
	_foldTable.draw(_cameraOne, &_blur, &_barrelTexture);

	//Draw the single sofa and apply toon shading
	_singleSofa.transform.SetPosition(vec3(-1.75f, 0.0f, 0.0f));
	_singleSofa.transform.SetRotation(vec3(0.0f, 0.0f, 0.0f));
	_singleSofa.transform.SetScale(vec3(1.0f, 1.0f, 1.0f));
	setToonLighting();
	_singleSofa.updateCollisionSphere(_singleSofa.transform.GetPosition(), 0.50f);
	_singleSofa.draw(_cameraOne, &_toon, &_barrelTexture);

	//Draw a book and apply the seizure inducing shader to it
	_book.transform.SetPosition(vec3(-0.5f, -0.5f, 0.0f));
	_book.transform.SetRotation(vec3(0.0f, 0.0f, 0.0f));
	_book.transform.SetScale(vec3(2.0f, 2.0f, 2.0f));
	setFunkyLighting();
	_book.updateCollisionSphere(_book.transform.GetPosition(), 0.50f);
	_book.draw(_cameraOne, &_funkyColour, &_barrelTexture);
}
//Setting the uniforms inside the toon shader
void MainGame::setToonLighting()
{
	_toon.bindShader();
	_toon.setVec3("lightDir", vec3(1.0f, 1.0f, 1.0f));
}
//Same for funky
void MainGame::setFunkyLighting()
{
	_funkyColour.bindShader();
	//Setting the uniform before drawing
	GLuint timeLocation = _funkyColour.getUniformLocation("time");
	//Sending the variable (1f symbolises there is 1 Float)
	glUniform1f(timeLocation, _time);
}
//And again...
void MainGame::setBlurLighting()
{
	_blur.bindShader();
	_blur.setVec4("InnerColor", 0.0f, 6.0f, 1.0f, 1.0f);
	_blur.setVec4("OuterColor",  12.0f, 0.0f, 0.0f, 1.0f);
	_blur.setFloat("RadiusInner", 1.5f);
	_blur.setFloat("RadiusOuter", 5.0f);
}
//....
void MainGame::setRimShading()
{	
	_rim.setMat4("u_vm", _cameraOne.GetView());
	_rim.setMat4("u_pm", _cameraOne.GetProjection());
}
//..
void MainGame::setADSLighting()
{
	_ADS.bindShader();
	_modelView = transform.GetModel() * _cameraOne.GetView();

	_ADS.setMat4("ModelViewMatrix", _modelView);
	_ADS.setMat4("ProjectionMatrix", _cameraOne.GetProjection());

	mat4 normalMatrix = transpose(inverse(_modelView));

	_ADS.setMat4("NormalMatrix", normalMatrix);
	_ADS.setVec4("Light.Position", vec4(0.0f, 3.0f, 2.0f, 1.0f));
	_ADS.setVec3("Light.La", vec3(0.5f, 0.5f, 0.5f));
	_ADS.setVec3("Light.Ld", vec3(2.0f, 2.0f, 2.0f));
	_ADS.setVec3("Light.Ls", vec3(0.9f, 0.9f, 0.9f));
	_ADS.setVec3("Material.Ka", vec3(1.0f, 2.5f, 1.0f));
	_ADS.setVec3("Material.Kd", vec3(3.0f, 1.0f, 1.0f));
	_ADS.setVec3("Material.Ks", vec3(3.0f, 3.0f, 3.0f));
	_ADS.setFloat("Shininess", 3.0f);
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

