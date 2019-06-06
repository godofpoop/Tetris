#pragma once
#include <al.h>
#include <alc.h>
#include <fstream>
#include <iostream>
#include <vector>

class Sound {
public:
	Sound();
	Sound(std::string path,bool loop);
	bool playing;
	bool looping;
	int source_state;
	void play();
	void stop();
	ALuint source;

	~Sound();
private:
	ALuint buffer;
	ALenum format;
	char* data;
	ALsizei size;
	ALsizei freq;
};
class SoundSystem 
{
public:
	SoundSystem();
	void addSound(Sound& s);
	void init();
	void update();
	void list_audio_devices(const ALCchar* devices);
	~SoundSystem();
private:
	char* data;
	int source_state;
	ALuint buffer;
	ALuint source;
	ALsizei size, freq;
	ALenum format;
	ALboolean loop = AL_FALSE;
	std::vector<Sound*> sounds;
	ALCdevice* device;
	ALCcontext* context;

};

