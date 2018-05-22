#pragma warning(disable: 4996)

#include <iostream>
#include "AudioManager.h"
#include "window.h"

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char** argv) {

	int width = 640, height = 480;
	
	Window window(height, width);
	window.update();
	AudioManager am;
	
	am.Play("./res/audio/bounce.wav");
	am.~AudioManager();
	window.~Window();

	system("pause");
	return 0;
	
}
