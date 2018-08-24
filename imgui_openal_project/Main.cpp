#include "window.h"

int main(int argc, char** argv) {
	//video
	const int width = 640, height = 480;
	Window window(height, width);
	//audio
	SDL_Event event;
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
					default:
						std::cout << "ERROR::INPUT: INPUT NOT BOUND" << std::endl;
						break;
				}
			}
		}
	}
	window.~Window();
	return 0;
}
