#include "window.h"

Window::Window(int height, int width)
{
	this->window = NULL;
	this->screenSurface = NULL;
	this->height = height;
	this->width = width;

	createWindow();
}

Window::~Window()
{
	//Destroy window
	SDL_DestroyWindow(window);
	//Quit SDL subsystems
	SDL_Quit();
}

SDL_Window * Window::getWindow()
{
	return this->window;
}

SDL_Surface * Window::getSurface()
{
	return this->screenSurface;
}

void Window::update()
{
	draw();
	//Update the surface
	SDL_UpdateWindowSurface(this->window);

	//ms
	SDL_Delay(2000);
}

void Window::createWindow()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else {
		//Create window
		this->window = SDL_CreateWindow("Lrssn Audio", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->width, this->height, SDL_WINDOW_SHOWN);
		if (this->window == NULL) {
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else {
			//Get window surface
			this->screenSurface = SDL_GetWindowSurface(this->window);
			//Fill the surface white
			SDL_FillRect(this->screenSurface, NULL, SDL_MapRGB(this->screenSurface->format, 255, 0, 0));
		}
	}
}

void Window::draw()
{

}
