#pragma once

#include <iostream>
#include <string>
#include <al.h>
#include <alc.h>
#include "AudioSource.h"

class AudioManager {
public:
	AudioManager();
	~AudioManager();
	void setVolume(ALfloat vol);
	ALfloat getVolume();
	void Play(AudioSource* soundSource);
private:
	ALint state;
	ALfloat volume;
	ALfloat listenerPos[3] = {0.0, 0.0, 0.0};
	ALfloat listenerVel[3] = {0.0, 0.0, 0.0};
	ALfloat listenerOri[6] = {0.0, 0.0, -1.0, 0.0, 1.0, 0.0};
};
