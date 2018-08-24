#pragma once
#include <iostream>
#include <AL/alut.h>
#include <vector>

class AudioSource {
public:
	AudioSource();
	AudioSource(const char* _src, const char* _name);
	~AudioSource();
	//set pitch, volume, position osv
	void setPitch(ALfloat _pitch);
	void setVolume(ALfloat _vol);
	void setLooping(ALboolean _loop);
	void setPosition(ALfloat _xp, ALfloat _yp, ALfloat _zp);
	void setVelocity(ALfloat _xv, ALfloat _yv, ALfloat _zv);
	void setDirection(ALfloat _xd, ALfloat _yd, ALfloat _zd);
	void setName(const char* _name);
	void setSource(const char* _src);
	//get pitch, volume, position osv
	ALuint getSourceId();
	ALfloat getPitch();
	ALfloat getVolume();
	ALboolean getLooping();
	const char* getSource();
	const char* getName();
	std::vector<float> *getPosition();
	std::vector<float> *getVelocity();
	std::vector<float> *getDirection();

	
private:
	void loadSource();
	const char*  source,* name;
	ALuint bufferId, sourceId;
	ALfloat pitch, volume;
	ALboolean isLooping;
	std::vector<float>  pos[3], dir[3], vel[3];

};
