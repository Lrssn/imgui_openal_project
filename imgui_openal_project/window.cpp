#include "window.h"

Window::Window(int _height, int _width){
	this->window = nullptr;
	this->screenSurface = nullptr;
	this->height = _height;
	this->width = _width;
	this->running = true;
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
	//SDL_Delay(750);
}

bool Window::isRunning() {
	return this->running;
}

void Window::stop() {
	this->running = false;
}

[[deprecated("Replaced by loadImage")]]
SDL_Surface* Window::loadSurface(const std::string &_imagePath) {
	//The final optimized image
	SDL_Surface* optimizedSurface = nullptr;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(_imagePath.c_str());
	if (loadedSurface == nullptr) {
		printf("Unable to load image %s! SDL_image Error: %s\n", _imagePath.c_str(), IMG_GetError());
	}
	else {
		//Convert surface to screen format
		//this line does not work
		//optimizedSurface = SDL_ConvertSurface(loadedSurface, .format, NULL);
		if (optimizedSurface == nullptr)
		{
			printf("Unable to optimize image %s! SDL Error: %s\n", _imagePath.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return optimizedSurface;
}

 void Window::loadImage(const std::string &_imagePath) const
{
	SDL_Surface* imageSurface = IMG_Load(_imagePath.c_str());
	if(imageSurface == nullptr) {
			printf("Unable to load image %s! SDL_image Error: %s\n", _imagePath.c_str(), IMG_GetError());
			SDL_DestroyRenderer(renderer);
			SDL_DestroyWindow(this->window);
	}
	SDL_BlitSurface(imageSurface, nullptr, this->screenSurface, nullptr);
}

void Window::createWindow(){
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}else {
		//Create window
		this->window = SDL_CreateWindow("Lrssn Audio", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->width, this->height, SDL_WINDOW_SHOWN);
		if (this->window == nullptr) {
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}else {
			//Get window surface
			this->screenSurface = SDL_GetWindowSurface(this->window);
			//Fill the surface white
			SDL_FillRect(this->screenSurface, NULL, SDL_MapRGB(this->screenSurface->format, 255, 0, 0));
			renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (renderer == nullptr) {
				SDL_DestroyWindow(this->window);
				std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
			}
		}
	}
}

void Window::draw(){
	loadImage("res/images/aurora_400.jpg");
}
