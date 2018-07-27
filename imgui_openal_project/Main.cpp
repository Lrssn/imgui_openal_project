#include <iostream>
#include "AudioManager.h"
#include "AudioSource.h"
#include "window.h"

int main(int argc, char** argv) {
	
	//video
	const int width = 640, height = 480;
	Window window(height, width);
	window.update();

	//audio
	AudioManager am;
	AudioSource as("./res/audio/bounce.wav");
	SDL_Event event;

	am.setVolume(1.5);
	while (window.isRunning()) {
		window.update();
		while (SDL_PollEvent(&event) != NULL) {
			//User requests quit
			if (event.type == SDL_QUIT) {
				window.stop();
			}
			else if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym){
					case SDLK_ESCAPE:
						window.stop();
						break;
					case SDLK_e:
						am.Play(&as);
						break;
					case SDLK_a:
						as.setPitch(2.0);
						break;
					case SDLK_s:
						as.setPitch(1.0);
						break;
				}
			}
		}
	}
	
	as.~AudioSource();
	am.~AudioManager();
	window.~Window();

	return 0;
}
