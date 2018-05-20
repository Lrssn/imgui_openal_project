#pragma warning(disable: 4996)

#include <iostream>
#include <al.h>
#include <alc.h>
#include <AL/alut.h>
#include <SDL.h>
#include <SDL_main.h>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char** argv) {
	ALuint buffer1, source1, buffer2, source2;
	ALint state;
	//The window we'll be rendering to
	SDL_Window* window = NULL;

	//The surface contained by the window
	SDL_Surface* screenSurface = NULL;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0){
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}else{
		//Create window
		window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL){
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}else{
			//Get window surface
			screenSurface = SDL_GetWindowSurface(window);

			//Fill the surface white
			SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

			//Update the surface
			SDL_UpdateWindowSurface(window);

			//Wait two seconds
			SDL_Delay(2000);
		}
	}

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
	//alSourcePlay(source1);
	alSourcePlay(source2);
	// Wait for the song to complete
	do {
		alGetSourcei(source2, AL_SOURCE_STATE, &state);
	} while (state == AL_PLAYING);

	// Clean up sources and buffers
	alDeleteSources(1, &source1);
	alDeleteBuffers(1, &buffer1);
	alDeleteSources(1, &source2);
	alDeleteBuffers(1, &buffer2);

	
	// Exit everything
	//Destroy window
	SDL_DestroyWindow(window);
	//Quit SDL subsystems
	SDL_Quit();
	//Quit alut subsystems
	alutExit();


	system("pause");
	return 0;
	
}
