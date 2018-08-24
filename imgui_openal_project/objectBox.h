#pragma once
#include "AudioSource.h"

class objectBox
{
public:
	objectBox();
	objectBox(const char* _src, const char* _name);
	~objectBox();
	void setit();
	AudioSource getAudioSource();
private:
	const char* audiosource;
	const char* audioname;
	AudioSource as;

};