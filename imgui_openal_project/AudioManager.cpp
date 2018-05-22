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
	// Clean up sources and buffers
	alDeleteSources(1, &this->source);
	alDeleteBuffers(1, &this->buffer);
	alutExit();
}

void AudioManager::Play(const char* src)
{
	this->soundSource = src;
	LoadSource();
	// Play
	alSourcePlay(this->source);
	// Wait for the song to complete
	do {
		alGetSourcei(this->source, AL_SOURCE_STATE, &this->state);
	} while (this->state == AL_PLAYING);
}

void AudioManager::LoadSource()
{
	// Load pcm data into buffer
	this->buffer = alutCreateBufferFromFile(this->soundSource);
	// Create sound source (use buffer to fill source)
	alGenSources(1, &this->source);
	alSourcei(this->source, AL_BUFFER, this->buffer);
}
