#pragma once

#include <fmod.hpp>

#include <string>
#include <map>

class CAudio
{
public:
	CAudio();//constructor
	~CAudio();//destructor
	bool initalise();//initalise audio system
	void update() { audioSystem->update(); }//update audio system
	bool loadSound(std::string filename, std::string name, bool loop);//load a sound with a name
	bool playSound(std::string name, float volume);//play sound from name

private:
	FMOD::System* audioSystem;//audio system
	std::map<std::string, FMOD::Sound*> sounds;//map of sounds
};