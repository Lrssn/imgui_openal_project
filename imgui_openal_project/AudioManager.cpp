#include "AudioManager.h"

AudioManager::AudioManager()
{
	// Initialize the environment
	alutInit(0, nullptr);
	if (alutGetError())
		std::cout << "ALUT::INIT::ERROR::" << alutGetErrorString(alutGetError()) << std::endl;
	this->masterVolume = 1.0f;
}

AudioManager::~AudioManager()
{
	//bgMusic.join();
	//effects.join();
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
	std::cout << "played: " << _soundSource->getSourceId() << std::endl;
	//std::thread bgMusic(tPLay, &_soundSource);
	alSourcePlay(_soundSource->getSourceId());
	if (alutGetError())
		std::cout << alutGetErrorString(alutGetError()) << std::endl;
	do {
		alGetSourcei(_soundSource->getSourceId(), AL_SOURCE_STATE, &this->state);
	} while (this->state == AL_PLAYING);
}

