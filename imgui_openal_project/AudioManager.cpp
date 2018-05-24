#include "AudioManager.h"

AudioManager::AudioManager()
{
	// Initialize the environment
	alutInit(0, NULL);
	// Capture errors
	alGetError();
}

AudioManager::~AudioManager()
{
	alutExit();
}

void AudioManager::setVolume(ALfloat vol)
{
	//set volume
	volume = vol;
	alListenerf(AL_GAIN, volume);
	std::cout << "Volume set to: " << (float)this->volume << std::endl;
}

ALfloat AudioManager::getVolume()
{
	alGetListenerf(AL_GAIN, &this->volume);
	return this->volume;
}

void AudioManager::Play(AudioSource* soundSource)
{

	//Play
	alSourcePlay(soundSource->getSourceId());
	// Wait for the song to complete
	do {
		alGetSourcei(soundSource->getSourceId(), AL_SOURCE_STATE, &this->state);
	} while (this->state == AL_PLAYING);
}

