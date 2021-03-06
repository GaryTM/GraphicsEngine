#include <iostream>
#include <SDL\SDL.h>
#include <cstdlib>
#include <cassert>;

#include"Errors.hpp"

//Write an error to the screen allowing the user to press any key to quit the game
void fatalError(string errorString)
{
	cout << errorString << endl;
	cout << "Press any key to exit..";
	assert(false);
	int tmp;
	cin >> tmp;
	SDL_Quit();
	exit(1);
}