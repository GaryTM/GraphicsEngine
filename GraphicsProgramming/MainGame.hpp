#pragma once
#include <SDL\SDL.h>
#include <GL\glew.h>

#include "Window.hpp"
#include "Shader.hpp"
#include "Sprite.hpp"
#include "Model.hpp"
#include "MoveableModel.hpp"
#include "Texture.hpp"
#include "Transform.hpp"
#include "CameraOne.hpp"
#include "Audio.hpp"
#include "Input.hpp"

using namespace std;
enum class GameState { PLAY, EXIT };

class MainGame
{
public:
	MainGame();
	~MainGame();
	//Used to run the game.. surprisingly enough.
	void run(); 
	
private:
	//Holds a pointer to the window used to display the program
	//Initialises required systems for set up (OpenGL, SDL etc.)
	void initSystems();
	//Initisalises the shaders
	void initShaders();
	//How collisions between models will be checked
	bool collision(vec3 model1Position, float model1Radius, vec3 model2Position, float model2Radius);
	//A loop which uses a game state to continuously loop until the user exits
	void gameLoop();
	//Used to handle user inputs (key presses, mouse clicks etc.)
	void processInput();
	//Used to draw everything required for the program
	void draw();
	void CreateTheModels();
	void setToonLighting();
	void setFunkyLighting();
	void setBlurLighting();
	void setRimShading();
	void setADSLighting();
	//An instance of the window class used for the main game window display
	Window _gameWindow;
	//Used to keep track of which state the program is currently in
	GameState _currentGameState;
	Sprite _sprite;
	Texture _barrelTexture;
	Texture _wallTexture;
	Texture _woodDoorTexture;
	//An instance of the shader which is a mix of the vert and frag shaders
	Shader _funkyColour;
	Shader _solidColour;
	Shader _toon;
	Shader _blur;
	Shader _ADS;
	Shader _rim;
	Shader _fog;
	Shader _textured;
	Model _sofa;
	Model _singleSofa;
	Model _foldTable;
	Model _book;
	Audio _audioDevice;
	CameraOne _cameraOne;
	Input _input;
	mat4 _modelView;
	float _time;
	float _ticker;
};

