#pragma once

#include <vector>

using namespace std;

//This is a static class meaning it only stores static methods and can only be instantiated once
class IOManager
{
public:
	//This will create a reference to buffer when called
	static bool readFileToBuffer(string filePath, vector<char>& buffer);
};

