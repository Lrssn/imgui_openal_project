#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_main.h>

class Window{
public: 
	Window(int height, int width);
	~Window();
	SDL_Window* getWindow();
	SDL_Surface* getSurface();
	void update();
private:
	void createWindow();
	void createRenderer();
	void draw();
	int height, width;
	//The window we'll be rendering to
	SDL_Window* window;
	//The surface contained by the window
	SDL_Surface* screenSurface;
	//The renderer for our window
	SDL_Renderer* renderer;
};