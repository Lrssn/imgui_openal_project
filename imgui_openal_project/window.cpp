#include "window.h"

Window::Window(int _height, int _width){
	this->window = nullptr;
	this->screenSurface = nullptr;
	this->height = _height;
	this->width = _width;
	this->running = true;
	createWindow();
	this->audioSources.emplace_back(AudioSource("./res/audio/imperial_march.wav", "Background music"));
	AudioSource as = AudioSource("./res/audio/bounce.wav", "effect");
	this->audioSources.emplace_back(as);
	this->vol = (float)this->am.getVolume();
}

Window::~Window(){
	//Destroy window
	ImGui_ImplSdlGL3_Shutdown();
	ImGui::DestroyContext(ImGui::CreateContext());
	SDL_GL_DeleteContext(gl_context);
	SDL_DestroyWindow(window);
	//Quit SDL subsystems
	SDL_Quit();
	for(int i = 0; i< this->audioSources.size();i++){
		this->audioSources.at(i).~AudioSource();
	}
	this->am.~AudioManager();
}

SDL_Window* Window::getWindow(){
	return this->window;
}

SDL_Surface* Window::getSurface(){
	return this->screenSurface;
}

void Window::update(){
	draw();
	
	//loadSurface("res/images/aurora_400.jpg", *this->screenSurface);
	// Rendering
	glViewport(0, 0, (int)ImGui::GetIO().DisplaySize.x, (int)ImGui::GetIO().DisplaySize.y);
	glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
	glClear(GL_COLOR_BUFFER_BIT);
	ImGui::Render();
	ImGui_ImplSdlGL3_RenderDrawData(ImGui::GetDrawData());
	SDL_GL_SwapWindow(window);
	//Update the surface
	//SDL_UpdateWindowSurface(this->window);
	
}

bool Window::getRunning() {
	return this->running;
}

void Window::stop() {
	this->running = false;
}

[[deprecated("Replaced by loadImage")]]
SDL_Surface* loadSurface(const std::string &_imagePath, SDL_Surface &_screenSurface) {
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
		optimizedSurface = SDL_ConvertSurface(loadedSurface, _screenSurface.format, NULL);
		if (optimizedSurface == nullptr)
		{
			printf("Unable to optimize image %s! SDL Error: %s\n", _imagePath.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return optimizedSurface;
}


const void Window::loadImage(const std::string &_imagePath)
{

	SDL_Surface* imageSurface = IMG_Load(_imagePath.c_str());
	if(imageSurface == nullptr) {
			printf("Unable to load image %s! SDL_image Error: %s\n", _imagePath.c_str(), IMG_GetError());
			SDL_DestroyRenderer(renderer);
			SDL_DestroyWindow(this->window);
	}
	//SDL_BlitSurface(imageSurface, nullptr, this->screenSurface, nullptr);
	//Apply the image stretched
	SDL_Rect stretchRect;
	stretchRect.x = 0;
	stretchRect.y = 0;
	stretchRect.w = this->width;
	stretchRect.h = this->height;
	SDL_BlitScaled(imageSurface, NULL, this->screenSurface, &stretchRect);

}

void Window::createWindow(){
	// initialize SDL and OpenGL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}else {
		//Create window
		// Setup window
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
		SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
		this->window = SDL_CreateWindow("Lrssn Audio", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->width, this->height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE); // SDL_WINDOW_SHOWN);
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
	
	SDL_DisplayMode current;
	SDL_GetCurrentDisplayMode(0, &current);
	//SDL_Window* window = SDL_CreateWindow("ImGui SDL2+OpenGL3 example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	gl_context = SDL_GL_CreateContext(this->window);
	SDL_GL_SetSwapInterval(1); // Enable vsync
	glewInit();
	
	// initialize imgui
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
	ImGui_ImplSdlGL3_Init(this->window);
	
	// Set Imgui colorstyle
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	//loadImage("res/images/aurora_400.jpg");
}

void Window::draw(){
	//create new imguiframe
	ImGui_ImplSdlGL3_NewFrame(this->window);

	// 1. Show a simple window.
	// Tip: if we don't call ImGui::Begin()/ImGui::End() the widgets automatically appears in a window called "Debug".
	ImGui::Begin("fps");
	ImGui::Text("Application average %.3f ms/frame (FPS %.1f)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color
	ImGui::End();

	ImGui::SliderFloat("volume", &vol, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f with 3 decimals   
	if(this->vol != this->am.getVolume())
		this->am.setVolume(vol);
	
	ImGui::Text("PLAY");
	for (uint16_t i = 0; i < this->audioSources.size();i++){	
		if(i!=0)
			ImGui::SameLine();
		if (ImGui::Button(this->audioSources.at(i).getName()))
			this->am.Play(&this->audioSources.at(i));
	}

	if (ImGui::Button("Quit"))
		this->stop();
	
	if (ImGui::Button("bg"))
		this->am.Play(&this->as1);
		
}


