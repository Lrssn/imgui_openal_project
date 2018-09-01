#include "window.h"
#include <thread>
int main(int argc, char** argv) {
	//video
	const int width = 640, height = 480;
	Window window(height, width);
	//audio
	
	SDL_Event event;
	//std::thread t1;
	AudioSource as = AudioSource("./res/audio/imperial_march.wav", "clang");
	//t1 = std::thread(&AudioManager::Play, std::ref(as));
	std::thread t1([&](AudioManager* tam) { tam->Play(&as); }, window.getAudioManager());
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
					case SDLK_a:
						//t1 = std::thread(&AudioManager::Play, am, &as);
						break;
					default:
						std::cout << "ERROR::INPUT: INPUT NOT BOUND" << std::endl;
						break;
				}
			}
		}
	}
	
	window.~Window();
	t1.join();
	as.~AudioSource();
	
	return 0;
}
