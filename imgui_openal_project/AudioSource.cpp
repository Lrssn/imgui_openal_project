#include "AudioSource.h"

AudioSource::AudioSource(const char * _src)
{
	this->source = _src;
	LoadSource();
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
		std::cout << "Audiosource nr: " << this->sourceId << " is now looping" << std::endl;
	else
		std::cout << "Audiosource nr: " << this->sourceId << " is no longer looping" << std::endl;

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

void AudioSource::LoadSource()
{
		// Load pcm data into buffer
		this->bufferId = alutCreateBufferFromFile(this->source);
		// Create sound source (use buffer to fill source)
		alGenSources(1, &this->sourceId);
		alSourcei(this->sourceId, AL_BUFFER, this->bufferId);
}
