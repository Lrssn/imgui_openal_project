#include "AudioSource.h"
#include <vector>

AudioSource::AudioSource()
{
	this->source = "";
	this->name = "";
	this->pos->push_back(0);
	this->pos->push_back(0);
	this->pos->push_back(0);
	this->vel->push_back(0);
	this->vel->push_back(0);
	this->vel->push_back(0);
	this->dir->push_back(0);
	this->dir->push_back(0);
	this->dir->push_back(0);
}

AudioSource::AudioSource(const char * _src, const char* _name)
{
	this->source = _src;
	this->name = _name;
	this->pos->push_back(0);
	this->pos->push_back(0);
	this->pos->push_back(0);
	this->vel->push_back(0);
	this->vel->push_back(0);
	this->vel->push_back(0);
	this->dir->push_back(0);
	this->dir->push_back(0);
	this->dir->push_back(0);
	loadSource();
}

AudioSource::~AudioSource()
{
	alDeleteSources(1, &this->sourceId);
	alDeleteBuffers(1, &this->bufferId);
}

void AudioSource::setPitch(ALfloat _pitch)
{
	this->pitch = _pitch;
	alSourcef(this->sourceId, AL_PITCH, this->pitch);
	std::cout << "Pitch set to: " << (float)(this->pitch) << std::endl;
}

void AudioSource::setVolume(ALfloat _vol)
{
	this->volume = _vol;
	alSourcef(this->sourceId, AL_GAIN, this->volume);
	std::cout << "Volume set to: " << (float)this->volume << std::endl;
}

void AudioSource::setLooping(ALboolean _loop)
{
	this->isLooping = _loop;
	alSourcei(this->sourceId, AL_LOOPING, (ALint)isLooping);
	if(isLooping)
		std::cout << "Audiosource: " << this->name << " is now looping" << std::endl;
	else
		std::cout << "Audiosource: " << this->name << " is no longer looping" << std::endl;

}
//in world coordinates
void AudioSource::setPosition(ALfloat _xp, ALfloat _yp, ALfloat _zp)
{
	this->pos->erase(this->pos->begin(), this->pos->end());
	this->pos->push_back(_xp);
	this->pos->push_back(_yp);
	this->pos->push_back(_zp);
	alSource3f(this->sourceId, AL_POSITION, pos->at(0), pos->at(1), pos->at(2));
}
//in world coordinates
void AudioSource::setVelocity(ALfloat _xv, ALfloat _yv, ALfloat _zv)
{
	this->vel->erase(this->vel->begin(), this->vel->end());
	this->vel->push_back(_xv);
	this->vel->push_back(_yv);
	this->vel->push_back(_zv);
	alSource3f(this->sourceId, AL_VELOCITY, vel->at(0), vel->at(1), vel->at(2));
}

void AudioSource::setDirection(ALfloat _xd, ALfloat _yd, ALfloat _zd)
{
	this->dir->erase(this->dir->begin(), this->dir->end());
	this->dir->push_back(_xd);
	this->dir->push_back(_yd);
	this->dir->push_back(_zd);
	alSource3f(this->sourceId, AL_DIRECTION, dir->at(0), dir->at(1), dir->at(2));
}

void AudioSource::setName(const char* _name)
{
	this->name = _name;
}


ALuint AudioSource::getSourceId()
{
	return this->sourceId;
}

ALfloat AudioSource::getPitch()
{
	return this->pitch;
}

ALfloat AudioSource::getVolume()
{
	return this->volume;
}

ALboolean AudioSource::getLooping()
{
	return this->isLooping;
}

void AudioSource::setSource(const char* _src)
{
	alDeleteSources(1, &this->sourceId);
	if (alutGetError())
		std::cout << "ALUT::DELETE1::ERROR::" << alutGetErrorString(alutGetError()) << std::endl;
	alDeleteBuffers(1, &this->bufferId);
	if (alutGetError())
		std::cout << "ALUT::DELETE2::ERROR::" << alutGetErrorString(alutGetError()) << std::endl;
	this->source = _src;
	loadSource();
	if (alutGetError())
		std::cout << "Source: " << this->name << " has been loaded with " << this->source << std::endl;
}

const char* AudioSource::getSource()
{
	return this->source;
}

const char* AudioSource::getName()
{
	return  this->name;
}

std::vector<float> *AudioSource::getPosition()
{
	//alGetSource3f(this->sourceId, AL_POSITION, &pos[0], &pos[1], &pos[2]);
	return this->pos;
}

std::vector<float> *AudioSource::getVelocity()
{
	//alGetSource3f(this->sourceId, AL_VELOCITY, &vel[0], &vel[1], &vel[2]);
	return this->vel;
}

std::vector<float> *AudioSource::getDirection()
{
	//alGetSource3f(this->sourceId, AL_DIRECTION, &dir[0], &dir[1], &dir[2]);
	return this->dir;
}

void AudioSource::loadSource()
{
		if(alutGetError())
			std::cout << "ALUT::PRE::ERROR::" << alutGetErrorString(alutGetError()) << std::endl;
		// Load pcm data into buffer
		this->bufferId = alutCreateBufferFromFile(this->source);
		if (alutGetError())
			std::cout << "ALUT::LOADBUFFER::ERROR::" << alutGetErrorString(alutGetError()) << std::endl;
		// Create sound source (use buffer to fill source)
		alGenSources(1, &this->sourceId);
		if (alutGetError())
			std::cout << "ALUT::GENSOURCE::ERROR::" << alutGetErrorString(alutGetError()) << std::endl;
		alSourcei(this->sourceId, AL_BUFFER, this->bufferId);
		if (alutGetError())
			std::cout << "ALUT::CONNECTSOURCETOBUFFER::ERROR::" << alutGetErrorString(alutGetError()) << std::endl;
}
