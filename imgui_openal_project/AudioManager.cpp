#include "AudioManager.h"

AudioManager::AudioManager()
{
	// Initialize the environment
	alutInit(0, nullptr);
	// Capture errors
	alGetError();
}

AudioManager::~AudioManager()
{
	alutExit();
}

void AudioManager::setVolume(ALfloat _vol)
{
	//set volume
	volume = _vol;
	alListenerf(AL_GAIN, volume);
	std::cout << "Volume set to: " << (float)this->volume << std::endl;
}

ALfloat AudioManager::getVolume()
{
	alGetListenerf(AL_GAIN, &this->volume);
	return this->volume;
}

void AudioManager::Play(AudioSource* _soundSource)
{

	//Play
	alSourcePlay(_soundSource->getSourceId());
	// Wait for the song to complete
	do {
		alGetSourcei(_soundSource->getSourceId(), AL_SOURCE_STATE, &this->state);
	} while (this->state == AL_PLAYING);
}

