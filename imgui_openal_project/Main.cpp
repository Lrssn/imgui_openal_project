#include <iostream>
#include "AudioManager.h"
#include "AudioSource.h"
#include "window.h"

int main(int argc, char** argv) {

	const int width = 640, height = 480;
	//video
	Window window(height, width);
	window.update();



	//audio
	AudioManager am;
	AudioSource as("./res/audio/bounce.wav");


	am.setVolume(1.5);
	am.Play(&as);
	as.setLooping(false);
	as.setPitch(2.0);
	am.Play(&as);
	as.~AudioSource();
	am.~AudioManager();
	window.~Window();

	getchar();
	return 0;
	
}
