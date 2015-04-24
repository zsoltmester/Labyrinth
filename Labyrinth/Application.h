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
#include "Mesh_OGL3.h"

class Application
{
public:
	Application(void);
	~Application(void);

	/*
	Initialize the application.
	*/
	bool initialize();

	/*
	Clean the application resources from memory.
	*/
	void clean();

	/*
	Update the app state. It has to be call on every frame and before render().
	*/
	void update();

	/*
	Redraw the screen on every frame. It has to be call on every frame.
	*/
	void render();


	//
	// Hardware controller callbacks
	//

	void keyboardDown(SDL_KeyboardEvent&);
	void keyboardUp(SDL_KeyboardEvent&);
	void mouseMove(SDL_MouseMotionEvent&);
	void mouseDown(SDL_MouseButtonEvent&);
	void mouseUp(SDL_MouseButtonEvent&);
	void mouseWheel(SDL_MouseWheelEvent&);

	/*
	Resize the screen, based on the given width and height.
	*/
	void resize(int width, int height);

private: 
	GLuint			m_textureID;

	gCamera			m_camera;
	gShaderProgram	m_program;
	gVertexBuffer	m_vb;

	Mesh			*m_mesh;
};

