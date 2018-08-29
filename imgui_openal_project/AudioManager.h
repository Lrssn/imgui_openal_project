#pragma once

#include <iostream>
#include <string>
#include <al.h>
#include <alc.h>
#include "AudioSource.h"
#include <thread>

class AudioManager {
public:
	AudioManager();
	~AudioManager();
	void setVolume(ALfloat _vol);
	ALfloat getVolume();
	void Play(AudioSource* _soundSource);
private:
	//std::thread bgMusic, effects;
	ALint state;
	std::thread t1;
	ALCdevice* Device;
	ALfloat masterVolume;
	ALfloat listenerPos[3] = {0.0, 0.0, 0.0};
	ALfloat listenerVel[3] = {0.0, 0.0, 0.0};
	ALfloat listenerOri[6] = {0.0, 0.0, -1.0, 0.0, 1.0, 0.0};
};
