#include "IOManager.hpp"

#include <fstream>

bool IOManager::readFileToBuffer(string filePath, vector<char>& buffer)
{
	/*Used to read in files in binary format symbolised by ios::binary
	(I have no idea what that means yet) then checking for errors*/
	ifstream file(filePath, ios::binary);
	if (file.fail())
	{
		perror(filePath.c_str());
		return false;
	}

	/*Reading the entire contents of the file into the buffer
	seekg is used to discover the size of a file by seeking to the end of the file.
	The parameters means seekg will seek up to 0 byte from the end of the file
	i.e THE END!*/
	file.seekg(0, ios::end);
	/*Getting the file size using tellg which returns an int containing 
	how many bytes have passed while searching giving the file size*/
	int fileSize = file.tellg();
	/*Seeking back to the beginning of the file because the file still has to be read*/
	file.seekg(0, ios::beg);
	//Disregarding the gubbins like a header etc. meaning the fileSize will reduce
	fileSize -= file.tellg();
	//Resizing the buffer size to be the size of fileSize (can I type size some more..)
	buffer.resize(fileSize);
	//Getting the first element in buffer by checking the address returning the c_str
	file.read(&(buffer[0]), fileSize);
	file.close();

	return true;
}
