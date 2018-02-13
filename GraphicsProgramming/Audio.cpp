#include "Audio.hpp"
#include "Errors.hpp"

Audio::Audio()
{
	//This is how the sound card is accessed
	device = alcOpenDevice(NULL);
	if (device == NULL)
	{
		fatalError("Sound card cannot be accessed!");
	}
	//This is how the context is created
	context = alcCreateContext(device, NULL);

	if (context == NULL)
	{
		fatalError("Context cannot be created!");
	}

	alcMakeContextCurrent(context);
}

Audio::~Audio()
{
	for (unsigned int i = 0; i < datas.size(); i++)
	{
		alDeleteSources(1, (unsigned int*)&datas[i].sourceID);
		if (datas[i].bufferID != -1)
		{
			alDeleteBuffers(1, (unsigned int*)&datas[i].bufferID);
			delete[] datas[i].buffer;
		}
	}
	alcDestroyContext(context);
	alcCloseDevice(device);
}

bool Audio::isBigEndian()
{
	int a = 1;
	return !((char*)&a)[0];
}

int Audio::convertToInt(char* buffer, int length)
{
	int a = 0;
	if (!isBigEndian())
		for (int i = 0; i < length; i++)
			((char*)&a)[i] = buffer[i];
	else
		for (int i = 0; i < length; i++)
			((char*)&a)[3 - i] = buffer[i];
	return a;
}

char* Audio::loadWAV(const char* fn, int& chan, int& samplerate, int& bps, int& size)
{
	char buffer[4];
	ifstream in(fn, ios::binary);
	in.read(buffer, 4);
	in.read(buffer, 4);
	in.read(buffer, 4); //WAV
	in.read(buffer, 4);	//fmt
	in.read(buffer, 4); //16 bit
	in.read(buffer, 2); //1
	in.read(buffer, 2);
	chan = convertToInt(buffer, 2);
	in.read(buffer, 4);
	samplerate = convertToInt(buffer, 4);
	in.read(buffer, 4);
	in.read(buffer, 2);
	in.read(buffer, 2);
	bps = convertToInt(buffer, 2);
	in.read(buffer, 4);
	in.read(buffer, 4);
	size = convertToInt(buffer, 4);

	char* soundData = new char[size];
	in.read(soundData, size);
	return soundData;
}

unsigned int Audio::loadAudioFile(const char* filename)
{
	bool found = false;
	unsigned int sourceID, bufferID;
	char* soundData = NULL;
	for (unsigned int i = 0; i < datas.size(); i++)
	{
		if (datas[i].name == filename && datas[i].bufferID != -1)
		{
			bufferID = datas[i].bufferID;
			found = true;
			break;
		}
	}
	if (!found)
	{
		int channel, sampleRate, bps, size;
		soundData = loadWAV(filename, channel, sampleRate, bps, size);
		unsigned int format;
		alGenBuffers(1, &bufferID);

		if (channel == 1)
		{
			if (bps == 8)
			{
				format = AL_FORMAT_MONO8;
			}
			else
			{
				format = AL_FORMAT_MONO16;
			}
		}
		else
		{
			if (bps == 8)
			{
				format = AL_FORMAT_STEREO8;
			}
			else
			{
				format = AL_FORMAT_STEREO16;
			}
		}
		alBufferData(bufferID, format, soundData, size, sampleRate);
	}
	alGenSources(1, &sourceID);
	alSourcei(sourceID, AL_BUFFER, bufferID);
	alSourcef(sourceID, AL_REFERENCE_DISTANCE, 1.0f);
	datas.push_back(Data(sourceID, (!found ? bufferID : -1), soundData, filename));
	return sourceID;
}

void Audio::deleteAudio(unsigned int id)
{
}

void Audio::playAudioID(unsigned int id)
{
	alSourcePlay(id);
}
void Audio::playAudio(unsigned int id, vec3& position)
{
	alSource3f(id, AL_POSITION, position.x, position.y, position.z);
	alSourcePlay(id);
}
void Audio::stopAudio(unsigned int id)
{
	alSourceStop(id);
}
void Audio::setListener(vec3 position, vec3& cameraLookAt)
{
	alListener3f(AL_POSITION, position.x, position.y, -position.z);
	float orinet[6] = { cameraLookAt.x, cameraLookAt.y, cameraLookAt.z,0,1,0 };
	alListenerfv(AL_ORIENTATION, orinet);
}