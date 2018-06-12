#include <iostream>
#include "AudioManager.h"
#include "AudioSource.h"
#include "window.h"

int main(int argc, char** argv) {

	int width = 640, height = 480;
	//video
	Window window(height, width);
	window.update();

<<<<<<< HEAD
	// Play
	alSourcePlay(source1);
	alSourcePlay(source2);
	// Wait for the song to complete
	do {
		alGetSourcei(source2, AL_SOURCE_STATE, &state);
	} while (state == AL_PLAYING);
	std::cout << "played sound" << std::endl;
=======
	//audio
	AudioManager am;
	AudioSource As("./res/audio/bounce.wav");
>>>>>>> 7a376c2d7fe38fb4a971d3ee06ae9c0878d457e9

	am.setVolume(1.5);
	am.Play(&As);
	As.setLooping(true);
	As.setPitch(2.0);
	am.Play(&As);
	As.~AudioSource();
	am.~AudioManager();
	window.~Window();

	system("pause");
	return 0;
	
}
