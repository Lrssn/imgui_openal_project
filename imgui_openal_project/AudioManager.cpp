#include "AudioManager.h"

AudioManager::AudioManager()
{
	// Initialize the environment
	alutInit(0, nullptr);
	// Capture errors
	alGetError();
	this->masterVolume = 1.0f;
}

AudioManager::~AudioManager()
{
	alutExit();
}

void AudioManager::setVolume(ALfloat _vol)
{
	//set volume
	masterVolume = (ALfloat)_vol;
	alListenerf(AL_GAIN, masterVolume);
	std::cout << "Volume set to: " << (float)this->masterVolume << std::endl;
}

ALfloat AudioManager::getVolume()
{
	alGetListenerf(AL_GAIN, &this->masterVolume);
	return this->masterVolume;
}

void AudioManager::Play(AudioSource* _soundSource)
{
	//Play
	alSourcePlay(_soundSource->getSourceId());
	std::cout << "Played audiosource: " << _soundSource->getName() << std::endl;
	// Wait for the song to complete
	do {
		alGetSourcei(_soundSource->getSourceId(), AL_SOURCE_STATE, &this->state);
	} while (this->state == AL_PLAYING);
}

