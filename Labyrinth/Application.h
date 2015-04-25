#pragma once

// GLEW
#include <GL/glew.h>

// SDL
#include <SDL.h>
#include <SDL_opengl.h>

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>

// External Utils
#include "gCamera.h"
#include "gShaderProgram.h"
#include "gVertexBuffer.h"

// Internal headers
#include "config.h"
#include "Field.h"

class Application
{
public:
	Application(void);
	~Application(void);

	// Application lifecycle events
	const bool onInitialize();
	void onUpdate();
	void onRender();
	void onClean();

	// Controller callbacks
	void onKeyboardDown(SDL_KeyboardEvent&);
	void onKeyboardUp(SDL_KeyboardEvent&);
	void onMouseMove(SDL_MouseMotionEvent&);
	void onMouseDown(SDL_MouseButtonEvent&);
	void onMouseUp(SDL_MouseButtonEvent&);
	void onMouseWheel(SDL_MouseWheelEvent&);
	void onResize(const int width,const int height);

	//helpers
	void drawWall(glm::mat4 matWorld);

private: 
	// managers
	gCamera			cameraManager;
	gShaderProgram	shaderManager;
	gVertexBuffer	vertexBufferManager;

	GLuint grassTextureID;
	GLuint wallTextureID;

	Field fields[config::MAP_SIZE][config::MAP_SIZE];
};

