#include <iostream>
#include <SDL\SDL.h>
#include"Errors.hpp"

void fatalError(string errorString)
{
	cout << errorString << endl;
	cout << "Press any key to exit..";
	int tmp;
	cin >> tmp;
	exit(1);
}