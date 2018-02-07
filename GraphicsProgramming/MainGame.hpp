#pragma once
#include <SDL\SDL.h>
#include <GL\glew.h>

#include "Shader.hpp"
#include "Sprite.hpp"

using namespace std;
enum class GameState { PLAY, EXIT };

class MainGame
{
public:
	MainGame();
	~MainGame();
	//Used to run the game.. surprisingly enough.
	void runGame(); 
	

private:
	//Holds a pointer to the window used to display the program
	SDL_Window* _gameWindow; 
	int _screenWidth;
	int _screenHeight;
	//Initialises required systems for set up (OpenGL, SDL etc.)
	void initSystems();
	//Initisalises the shaders
	void initShaders();
	//A loop which uses a game state to continuously loop until the user exits
	void gameLoop();
	//Used to handle user inputs (key presses, mouse clicks etc.)
	void processInput();
	//Used to draw everything required for the program
	void draw();
	//Used to keep track of which state the program is currently in
	GameState _currentGameState;
	Sprite _sprite;
	Shader _colourShader;
};

