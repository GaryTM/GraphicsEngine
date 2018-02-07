#pragma once
#include <string>

using namespace std;

/*Checks for a fatal error and writing the string to the console
the extern keyword informs OpenGL fatalError is defined elsewhere*/
extern void fatalError(string errorString);
