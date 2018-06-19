#include "window.h"

Window::Window(int _height, int _width){
	this->window = nullptr;
	this->screenSurface = nullptr;
	this->height = _height;
	this->width = _width;

	createWindow();
}

Window::~Window(){
	//Destroy window
	SDL_DestroyWindow(window);
	//Quit SDL subsystems
	SDL_Quit();
}

SDL_Window* Window::getWindow(){
	return this->window;
}

SDL_Surface* Window::getSurface(){
	return this->screenSurface;
}

void Window::update(){
	draw();
	//Update the surface
	SDL_UpdateWindowSurface(this->window);

	//ms
	SDL_Delay(750);
}

void Window::createWindow(){
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else {
		//Create window
		this->window = SDL_CreateWindow("Lrssn Audio", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->width, this->height, SDL_WINDOW_SHOWN);
		if (this->window == nullptr) {
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else {
			//Get window surface
			this->screenSurface = SDL_GetWindowSurface(this->window);
			//Fill the surface white
			SDL_FillRect(this->screenSurface, NULL, SDL_MapRGB(this->screenSurface->format, 255, 0, 0));
		}
	}

	//TODO: abstract
	SDL_Renderer *renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) {
		SDL_DestroyWindow(this->window);
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
	}
	std::string imagePath = "dumb.bmp";
	SDL_Surface *bmp = SDL_LoadBMP(imagePath.c_str());
	if (bmp == nullptr) {
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(this->window);
		std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
	}

}

void Window::draw(){

}
