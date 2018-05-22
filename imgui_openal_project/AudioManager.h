#pragma once

#include<string>
#include <al.h>
#include <alc.h>
#include <AL/alut.h>

class AudioManager {
public:
	AudioManager();
	~AudioManager();
	void Play(const char* src);
private:
	void LoadSource();
	const char*  soundSource;
	ALuint buffer, source;
	ALint state;
};
