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
	
	//loadSurface("res/images/aurora_400.jpg", *this->screenSurface);
	//Update the surface
	SDL_UpdateWindowSurface(this->window);
	//ms
	SDL_Delay(750);
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
	SDL_GLContext gl_context = SDL_GL_CreateContext(this->window);
	SDL_GL_SetSwapInterval(1); // Enable vsync
	gl3wInit();
	
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
	//ImGui_ImplSdlGL3_Init(this->window);
	// Setup style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	loadImage("res/images/aurora_400.jpg");
}

void Window::draw(){
	//ImGui_ImplSdlGL3_NewFrame(this->window);

	// 1. Show a simple window.
	// Tip: if we don't call ImGui::Begin()/ImGui::End() the widgets automatically appears in a window called "Debug".
	{
		static float f = 0.0f;
		static int counter = 0;
		ImGui::Text("Hello, world!");                           // Display some text (you can use a format string too)
		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f    
		ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

		ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our windows open/close state
		//ImGui::Checkbox("Another Window", &show_another_window);

		if (ImGui::Button("Button"))                            // Buttons return true when clicked (NB: most widgets return true when edited/activated)
			counter++;
		ImGui::SameLine();
		ImGui::Text("counter = %d", counter);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
}
