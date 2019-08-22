#include "Audio.h"

CAudio::CAudio(){}//constructor

CAudio::~CAudio()//deconstuctor
{
	for (auto it = sounds.begin(); it != sounds.end(); it++)//iterates through the sound and deletes them
	{
		(*it).second->release();
	}
	audioSystem->release();//releases the audio system
	audioSystem = 0;
}

bool CAudio::initalise()//creates and initalises the audio sysytem
{
	FMOD_RESULT result;//result for error checking
	result = FMOD::System_Create(&audioSystem);
	if (result != FMOD_OK) { return false; }

	result = audioSystem->init(100, FMOD_INIT_NORMAL | FMOD_INIT_3D_RIGHTHANDED, 0);
	if (result != FMOD_OK) { return false; }

	return true;
}

bool CAudio::loadSound(std::string filename, std::string name, bool loop)//loads a sound for use
{
	FMOD_RESULT result;//result for error checking
	FMOD::Sound* sound;
	if (loop)
	{
		result = audioSystem->createSound(filename.c_str(), FMOD_LOOP_NORMAL, 0, &sound);//create sound with loop
	}
	else
	{
		result = audioSystem->createSound(filename.c_str(), FMOD_DEFAULT, 0, &sound);//create sound without loop
	}
	if (result != FMOD_OK) { return false; }
	sounds[name] = sound;//add the sound to the map
	return true;
}

bool CAudio::playSound(std::string name, float volume)//plays a sound
{
	FMOD::Channel* channel;//channel for volume control
	FMOD_RESULT result;//result for error checking
	result = audioSystem->playSound(sounds[name], 0, false, &channel);//plays sound
	if (result != FMOD_OK) { return false; }
	channel->setVolume(volume);//sets volume
	return true;
}
