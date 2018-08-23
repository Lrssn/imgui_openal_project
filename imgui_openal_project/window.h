#pragma once

#include <iostream>
#include <stdio.h>
#include "./res/libs/imgui/imgui.h"
#include "./res/libs/imgui/imgui_impl_sdl_gl3.h"
#include <glew.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_main.h>
#include "AudioManager.h"

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
	bool running, show_demo_window;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	SDL_GLContext gl_context;
	//audio
	AudioManager am;
	std::vector<AudioSource> audioSources;
	AudioSource as1 = AudioSource("./res/audio/bounce.wav", "effect");
	float vol;

};