#pragma once

#include <fmod.hpp>

#include <string>
#include <map>
#include <filesystem>

class CAudio
{
public:
	~CAudio();//destructor
	bool initalise(std::string soundFolder);//initalise audio system
	void update() { audioSystem->update(); }//update audio system
	bool loadSound(std::string filename, std::string name, bool loop);//load a sound with a name
	bool playSound(std::string name, float volume);//play sound from name
	static CAudio* getInstance();
private:
	CAudio();//constructor
	FMOD::System* audioSystem;//audio system
	std::map<std::string, FMOD::Sound*> sounds;//map of sounds
	static CAudio* instance;
};