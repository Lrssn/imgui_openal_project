#include <iostream>
#include "AudioManager.h"
#include "AudioSource.h"
#include "window.h"

int main(int argc, char** argv) {

	int width = 640, height = 480;
	
	Window window(height, width);
	window.update();
	AudioManager am;
	AudioSource As("./res/audio/bounce.wav");

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
