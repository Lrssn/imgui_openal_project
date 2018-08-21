#include <iostream>
#include "AudioManager.h"
#include "AudioSource.h"
#include "window.h"

int main(int argc, char** argv) {
	
	//video
	const int width = 640, height = 480;
	Window window(height, width);
	window.update();
	std::vector<float> a;
	//audio
	AudioManager am;
	AudioSource as("./res/audio/bounce.wav", "Effects");
	SDL_Event event;
	int q = 0;
	am.setVolume(1.5);
	while (window.getRunning()) {
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
					case SDLK_t:
						if(q == 0){
							as.setSource("./res/audio/bounce.wav");
							q++;
						}else if(q == 1){
							as.setSource("./res/audio/guitar.wav");
							q++;
						}else if (q == 2) {
							as.setSource("./res/audio/clang.wav");
							q = 0;
						}
						break;
					case SDLK_u:
						as.setPosition(1.0f, 0.5f, 3.0f);
						as.setDirection(1.0f, 0.5f, 3.0f);
						as.setVelocity(10.0f, 1.5f, 6.0f);
						break;
					case SDLK_i:
						std::cout << "Position is: x=" << as.getPosition()->at(0) << ",  y = " << as.getPosition()->at(1) << ",  z = " << as.getPosition()->at(2) << std::endl;
						std::cout << "Direction is: x=" << as.getDirection()->at(0) << ",  y = " << as.getDirection()->at(1) << ",  z = " << as.getDirection()->at(2) << std::endl;
						std::cout << "Velocity is: x=" << as.getVelocity()->at(0) << ",  y = " << as.getVelocity()->at(1) << ",  z = " << as.getVelocity()->at(2) << std::endl;
						break;
					default:
						
						std::cout << "ERROR::INPUT: INPUT NOT BOUND" << std::endl;
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
