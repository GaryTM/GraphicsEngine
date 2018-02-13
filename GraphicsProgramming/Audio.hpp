#pragma once

#include <glm\glm.hpp>
#include <AL\al.h>
#include <AL\alc.h>
#include <vector>
#include <cstring>
#include <string>
#include <iostream>
#include <fstream>
#include <SDL\SDL.h>
#include <glm/gtc/type_ptr.hpp>

using namespace std;
using namespace glm;
class Audio
{
	struct Data {
		int sourceID, bufferID;
		char* buffer;
		string name;
		Data(unsigned int sI, unsigned int bI, char* b, const char* n)
		{
			this->sourceID = sI;
			this->bufferID = bI;
			this->buffer = b;
			this->name = n;
		}
	};

	struct Vector3
	{
		float x, y, z;
	};
	vector<Data> datas;
	ALCcontext* context;
	ALCdevice* device;
	bool isBigEndian();
	int convertToInt(char* buffer, int length);
	char* loadWAV(const char* fn, int& chan, int& samplerate, int& bps, int& size);

public:
	Audio();
	~Audio();
	unsigned int loadAudioFile(const char* filename);
	void deleteAudio(unsigned int id);
	void playAudioID(unsigned int id);
	void playAudio(unsigned int id, vec3& position);
	void stopAudio(unsigned int id);
	void setlistener(vec3& position, vec3& cameraLookAt);

private:
};

