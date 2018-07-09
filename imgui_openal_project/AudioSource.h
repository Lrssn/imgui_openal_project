#pragma once
#include <iostream>
#include <AL/alut.h>

class AudioSource {
public:
	AudioSource(const char* _src);
	~AudioSource();
	//set pitch, volume, position osv
	void setPitch(ALfloat _pitch);
	void setVolume(ALfloat _vol);
	void setLooping(ALboolean _loop);
	ALuint getSourceId();
	ALfloat getPitch();
	ALfloat getVolume();
	ALboolean getLooping();
	
private:
	void LoadSource();
	const char*  source;
	ALuint bufferId, sourceId;
	ALfloat pitch, volume;
	ALboolean isLooping;

};