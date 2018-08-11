#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_main.h>

class Window{
public: 
	Window(int _height, int _width);
	~Window();
	SDL_Window* getWindow();
	SDL_Surface* getSurface();
	void update();
	bool getRunning();
	void stop();
private:
	SDL_Surface* loadSurface(const std::string &_imagePath, SDL_Surface &_screenSurface);
	const void loadImage(const std::string &_imagePath);
	void createWindow();
	void draw();
	int height, width;
	//The window we'll be rendering to
	SDL_Window* window;
	//The surface contained by the window
	SDL_Surface* screenSurface;
	//The renderer for pictures
	SDL_Renderer* renderer;
	bool running;
};