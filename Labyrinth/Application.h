#pragma once

// GLEW
#include <GL/glew.h>

// SDL
#include <SDL.h>
#include <SDL_opengl.h>

// GLM
#define GLM_SWIZZLE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>

// External Utils
#include "gCamera.h"
#include "gShaderProgram.h"
#include "gVertexBuffer.h"
#include "Mesh_OGL3.h"

// Internal headers
#include "config.h"
#include "Field.h"
#include "Character.h"

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
	const glm::vec3 drawOrb(const float orbitRadius);

private: 
	// managers
	gCamera	cameraManager;
	gShaderProgram shaderManager;
	gVertexBuffer vertexBufferManager;

	int startOfQuadVertices;
	int numberOfQuadVertices;
	int startOfCuboidVertices;
	int numberOfCuboidVertices;
	int startOfCylinderShieldVertices;
	int numberOfCylinderShieldVertices;
	int startOfCylinderTopVertices;
	int numberOfCylinderTopVertices;
	int startOfCylinderBottomVertices;
	int numberOfCylinderBottomVertices;
	int startOfTopPyramidVertices;
	int numberOfTopPyramidVertices;
	int startOfBottomPyramidVertices;
	int numberOfBottomPyramidVertices;
	int startOfSphereVertices;
	int numberOfSphereVertices;

	GLuint grassTextureID;
	GLuint wallTextureID;
	GLuint coinTextureID;
	GLuint diamondTextureID;
	GLuint suzanneTextureID;

	Field fields[config::MAP_SIZE][config::MAP_SIZE];
	
	Hero* hero;
	Mesh* heroMesh;
};