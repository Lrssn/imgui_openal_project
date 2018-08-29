#pragma once
#include "AudioSource.h"

class objectBox
{
public:
	objectBox();
	~objectBox();
	AudioSource *getAudioSource();
private:
	AudioSource as = AudioSource("./res/audio/bounce.wav", "bounce");
};