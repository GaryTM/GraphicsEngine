#include <iostream>
#include <SDL\SDL.h>
#include <cstdlib>
#include"Errors.hpp"

void fatalError(string errorString)
{
	cout << errorString << endl;
	cout << "Press any key to exit..";
	int tmp;
	cin >> tmp;
	SDL_Quit();
	exit(1);
}