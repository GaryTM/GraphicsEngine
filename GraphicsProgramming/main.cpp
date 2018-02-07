#include <Windows.h>
#include <SDL\SDL.h>
#include<GL\glew.h>
#include <iostream>

#include "MainGame.hpp"

using namespace std;

int main(int argc, char** argv)
{
	//Creating an instance on the MainGame class named game
	MainGame game;
	//RUN THE GAME!
	game.runGame();

	return 0;
}