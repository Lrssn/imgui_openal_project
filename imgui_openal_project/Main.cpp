#pragma warning(disable: 4996)

#include <iostream>
#include <al.h>
#include <alc.h>
//#include <SDL_audio.h>
#include <AL/alut.h>



int main(int argc, char** argv) {
	ALuint buffer1, source1, buffer2, source2;
	ALint state;

	// Initialize the environment
	alutInit(0, NULL);

	// Capture errors
	alGetError();

	// Load pcm data into buffer
	buffer1 = alutCreateBufferFromFile("./res/audio/imperial_march.wav");
	buffer2 = alutCreateBufferFromFile("./res/audio/bounce.wav");
	// Create sound source (use buffer to fill source)
	alGenSources(1, &source1);
	alSourcei(source1, AL_BUFFER, buffer1);
	alGenSources(1, &source2);
	alSourcei(source2, AL_BUFFER, buffer2);

	// Play
	alSourcePlay(source1);
	alSourcePlay(source2);
	// Wait for the song to complete
	do {
		alGetSourcei(source1, AL_SOURCE_STATE, &state);
	} while (state == AL_PLAYING);

	// Clean up sources and buffers
	alDeleteSources(1, &source1);
	alDeleteBuffers(1, &buffer1);
	alDeleteSources(1, &source2);
	alDeleteBuffers(1, &buffer2);

	// Exit everything
	alutExit();
	system("pause");
	return 0;
	
}
