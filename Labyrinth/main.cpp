#include <GL/glew.h>

#include <SDL.h>
#include <SDL_opengl.h>

#include <iostream>

#include "Application.h"
#include "config.h"

// TODO move these functions to a helper class (name idea: ApplicationHelper)
// or to the Application
const int initializeSDL(SDL_Window*& window);
const int initializeOGL(SDL_Window *const window, SDL_GLContext& context);
const int initializeApp(SDL_Window *const window, Application& app);
void run(SDL_Window *const window, Application app);
void exit(SDL_Window *const window, SDL_GLContext context, Application app);
void wait();

int main(int argc, char* args[])
{
	SDL_Window* window = 0;
	SDL_GLContext context = 0;
	Application app;

	// Initialize SDL, OpenGL and the application
	if (initializeSDL(window) == -1
		|| initializeOGL(window, context) == -1
		|| initializeApp(window, app) == -1)
	{
		return -1;
	}

	// Run the application
	run(window, app);

	// Exit
	exit(window, context, app);
	atexit(wait);
}

const int initializeSDL(SDL_Window *&window)
{
	if (SDL_Init(SDL_INIT_VIDEO) == -1)
	{
		std::cout
			<< "[SDL Initialization] Error while Initializing SDL: "
			<< SDL_GetError() << std::endl;
		return -1;
	}

	// set color depth
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	
	// other options
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	// create window
	window = SDL_CreateWindow( // TODO
		"Labyrinth",
		0,						
		0,						
		config::SCREEN_RESOLUTION_WIDTH,						
		config::SCREEN_RESOLUTION_HEIGHT,
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_FULLSCREEN);


	if (window == 0)
	{
		std::cout << "[Create window] Error while creating window: " 
			<< SDL_GetError() << std::endl;
		return -1;
	}

	return 0;
}

const int initializeOGL(SDL_Window *const window, SDL_GLContext& context)
{
	context = SDL_GL_CreateContext(window);
	if (context == 0)
	{
		std::cout 
			<< "[OGL context initialization] Error while initializing OGL context: " 
			<< SDL_GetError() << std::endl;
		return -1;
	}

	// turn on vsync
	SDL_GL_SetSwapInterval(1);

	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		std::cout << "[GLEW] Error while initializing GLEW!" << std::endl;
		return -1;
	}

	int glVersion[2] = {-1, -1};
	glGetIntegerv(GL_MAJOR_VERSION, &glVersion[0]);
	glGetIntegerv(GL_MINOR_VERSION, &glVersion[1]);
	std::cout << "Running OpenGL " << glVersion[0] << "." << glVersion[1] << std::endl;

	if (glVersion[0] == -1 && glVersion[1] == -1)
	{
		SDL_GL_DeleteContext(context);
		SDL_DestroyWindow(window);

		std::cout << "[OGL context create] Error to create OGL context." << std::endl;
		return -1;
	}

	return 0;
}

const int initializeApp(SDL_Window *const window, Application& app)
{
	if (!app.onInitialize())
	{
		SDL_DestroyWindow(window);
		std::cout
			<< "[Application initialization] Error while initializing the application!"
			<< std::endl;
		return -1;
	}

	return 0;
}

void run(SDL_Window *const window, Application app)
{
	bool isRunning = true;
	while (isRunning)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				isRunning = false;
				break;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE)
				{
					isRunning = false;
				}
				app.onKeyboardDown(event.key);
				break;
			case SDL_KEYUP:
				app.onKeyboardUp(event.key);
				break;
			case SDL_MOUSEBUTTONDOWN:
				app.onMouseDown(event.button);
				break;
			case SDL_MOUSEBUTTONUP:
				app.onMouseUp(event.button);
				break;
			case SDL_MOUSEWHEEL:
				app.onMouseWheel(event.wheel);
				break;
			case SDL_MOUSEMOTION:
				app.onMouseMove(event.motion);
				break;
			case SDL_WINDOWEVENT:
				if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
				{
					app.onResize(event.window.data1, event.window.data2);
				}
				break;
			}
		}

		app.onUpdate();
		app.onRender();

		SDL_GL_SwapWindow(window);
	}
}

void exit(SDL_Window *const window, SDL_GLContext context, Application app)
{
	app.onClean();
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void wait()
{
	system("pause");
}