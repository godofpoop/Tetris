#include "SoundSystem.h"
#include "TetrisGame.h"

SoundSystem::SoundSystem()
{
}
void Sound::play()
{
	if (TetrisGame::soundopt) alSourcePlay(source);
}
void Sound::stop()
{
	alSourcePause(source);
}
void SoundSystem::init()
{
	ALchar* devices = nullptr;

	device = alcOpenDevice(NULL);
	if (!device) { std::cout << "Fucked up fam"; }

	ALboolean enumeration;

	enumeration = alcIsExtensionPresent(NULL, "ALC_ENUMERATION_EXT");
	if (enumeration == AL_FALSE)
		std::cout << "enum supported noice \n";
	else
		std::cout << "num not supported you fuck \n";

	list_audio_devices(alcGetString(NULL, ALC_DEVICE_SPECIFIER));

	ALCenum error;

	context = alcCreateContext(device, NULL);
	if (!alcMakeContextCurrent(context))
		std::cout << "Failed to make context \n";
}
void SoundSystem::list_audio_devices(const ALCchar * devices)
{
	const ALCchar* device = devices, * next = devices + 1;
	size_t len = 0;

	fprintf(stdout, "Devices list:\n");
	fprintf(stdout, "----------\n");
	while (device && *device != '\0' && next && *next != '\0') {
		fprintf(stdout, "%s\n", device);
		len = strlen(device);
		device += (len + 1);
		next += (len + 2);
	}
	fprintf(stdout, "----------\n");
}
void SoundSystem::update()
{
	
}

SoundSystem::~SoundSystem()
{
	device = alcGetContextsDevice(context);
	alcMakeContextCurrent(NULL);
	alcDestroyContext(context);
	alcCloseDevice(device);
}
Sound::Sound() : playing(0) {}
Sound::Sound(std::string path,bool loop) : playing(0)
{
	looping = loop;
	alGenSources((ALuint)1, &source);
	alSourcef(source, AL_PITCH, 2);
	alSourcef(source, AL_GAIN, 1);
	alSource3f(source, AL_POSITION, 0, 0, 10);
	alSource3f(source, AL_VELOCITY, 0, 0, 0);
	if(looping) alSourcei(source, AL_LOOPING, AL_TRUE);
	else alSourcei(source, AL_LOOPING, AL_FALSE);
	alGenBuffers((ALuint)1, &buffer);

	std::ifstream file(path, std::ios::in | std::ios::binary);

	char* integer = new char[4];
	char* idk = new char[2];

	int samplerate, subchunksize, byterate;
	short audioformat, numchannels, bitspersample,blockalign;

	file.read(integer, 4);
	file.read(integer, 4);
	file.read(integer, 4);
	memcpy(&samplerate, integer, 4);
	file.read(integer, 4);
	file.read(integer, 4);
	memcpy(&subchunksize, integer, 4);
	file.read(idk, 2);
	memcpy(&audioformat, idk, 2);
	file.read(idk, 2);
	memcpy(&numchannels, idk, 2);
	file.read(integer, 4);
	memcpy(&freq, integer, 4);
	file.read(integer, 4);
	memcpy(&byterate, integer, 4);
	file.read(idk, 2);
	memcpy(&blockalign, idk, 2);
	file.read(idk, 2);
	memcpy(&bitspersample, idk, 2);
	file.read(integer, 4);
	file.read(integer, 4);
	memcpy(&size, integer, 4);

	data = new char[size];
	file.read(data, size);

	bool stereo = (samplerate > 1);

	switch (bitspersample) {
	case 16:
		if (stereo)
			format = AL_FORMAT_STEREO16;
		else
			format = AL_FORMAT_MONO16;
	case 8:
		if (stereo)
			format = AL_FORMAT_STEREO8;
		else
			format = AL_FORMAT_MONO8;
	default:
		format = AL_FORMAT_MONO16;
	}
	alBufferData(buffer, format, data, size, freq);
	alSourcei(source, AL_BUFFER, buffer);
	alSourcePlay(source);
	alGetSourcei(source, AL_SOURCE_STATE, &source_state);
}
void SoundSystem::addSound(Sound& s)
{
	sounds.push_back(&s);
}
Sound::~Sound()
{
	alDeleteSources(1, &source);
	alDeleteBuffers(1, &buffer);
}