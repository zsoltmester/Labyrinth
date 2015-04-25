#include "Application.h"

#include <iostream>

#include "config.h"
#include "GLUtils.hpp"

//
// Helper functions
//

void createQuad(gVertexBuffer &vertexBufferManager, GLuint &grassTextureID)
{
	// position                                     x  y                   z
	vertexBufferManager.AddData(0,                 0, 0,                 0); // upper left
	vertexBufferManager.AddData(0,                 0, 0, config::QUAD_SIDE); // lower left
	vertexBufferManager.AddData(0, config::QUAD_SIDE, 0, config::QUAD_SIDE); // lower right
	vertexBufferManager.AddData(0, config::QUAD_SIDE, 0,                 0); // upper right

	// normal                      x  y  z
	vertexBufferManager.AddData(1, 0, 1, 0);
	vertexBufferManager.AddData(1, 0, 1, 0);
	vertexBufferManager.AddData(1, 0, 1, 0);
	vertexBufferManager.AddData(1, 0, 1, 0);

	// texture
	vertexBufferManager.AddData(2, 0, 0);
	vertexBufferManager.AddData(2, 1, 0);
	vertexBufferManager.AddData(2, 0, 1);
	vertexBufferManager.AddData(2, 1, 1);

	grassTextureID = TextureFromFile("texture_grass.jpg");
}

void createCuboid(gVertexBuffer &vertexBufferManager, GLuint &wallTextureID)
{
	//
	// position  
	//

	// upper side                                  x                    y                       z
	vertexBufferManager.AddData(0, config::QUAD_SIDE, config::WALL_HEIGHT, config::WALL_THICKNESS);
	vertexBufferManager.AddData(0, config::QUAD_SIDE, config::WALL_HEIGHT,                      0);
	vertexBufferManager.AddData(0,                 0, config::WALL_HEIGHT,                      0);
	vertexBufferManager.AddData(0,                 0, config::WALL_HEIGHT, config::WALL_THICKNESS);
	// height related 1. side  												
	vertexBufferManager.AddData(0, config::QUAD_SIDE,                   0, config::WALL_THICKNESS);
	vertexBufferManager.AddData(0, config::QUAD_SIDE, config::WALL_HEIGHT, config::WALL_THICKNESS);
	vertexBufferManager.AddData(0,                 0, config::WALL_HEIGHT, config::WALL_THICKNESS);
	vertexBufferManager.AddData(0,                 0,                   0, config::WALL_THICKNESS);
	// height related 2. side												
	vertexBufferManager.AddData(0,                 0,                   0,                      0);
	vertexBufferManager.AddData(0,                 0, config::WALL_HEIGHT,                      0);
	vertexBufferManager.AddData(0, config::QUAD_SIDE, config::WALL_HEIGHT,                      0);
	vertexBufferManager.AddData(0, config::QUAD_SIDE,                   0,                      0);
	// thick related 1. side												
	vertexBufferManager.AddData(0,                 0,                   0, config::WALL_THICKNESS);
	vertexBufferManager.AddData(0,                 0, config::WALL_HEIGHT, config::WALL_THICKNESS);
	vertexBufferManager.AddData(0,                 0, config::WALL_HEIGHT,                      0);
	vertexBufferManager.AddData(0,                 0,                   0,                      0);
	// thick related 2. side												                     
	vertexBufferManager.AddData(0, config::QUAD_SIDE,                   0,                      0);
	vertexBufferManager.AddData(0, config::QUAD_SIDE, config::WALL_HEIGHT,                      0);
	vertexBufferManager.AddData(0, config::QUAD_SIDE, config::WALL_HEIGHT, config::WALL_THICKNESS);
	vertexBufferManager.AddData(0, config::QUAD_SIDE,                   0, config::WALL_THICKNESS);

	//
	// TODO normal
	//

	// upper side                  x  y  z
	vertexBufferManager.AddData(1, 0, 1, 0);
	vertexBufferManager.AddData(1, 0, 1, 0);
	vertexBufferManager.AddData(1, 0, 1, 0);
	vertexBufferManager.AddData(1, 0, 1, 0);
	// height related 1. side
	vertexBufferManager.AddData(1, 0, 0, 0);
	vertexBufferManager.AddData(1, 0, 0, 0);
	vertexBufferManager.AddData(1, 0, 0, 0);
	vertexBufferManager.AddData(1, 0, 0, 0);
	// height related 2. side
	vertexBufferManager.AddData(1, 0, 0, 0);
	vertexBufferManager.AddData(1, 0, 0, 0);
	vertexBufferManager.AddData(1, 0, 0, 0);
	vertexBufferManager.AddData(1, 0, 0, 0);
	// thick related 1. side
	vertexBufferManager.AddData(1, 0, 0, 0);
	vertexBufferManager.AddData(1, 0, 0, 0);
	vertexBufferManager.AddData(1, 0, 0, 0);
	vertexBufferManager.AddData(1, 0, 0, 0);
	// thick related 2. side
	vertexBufferManager.AddData(1, 0, 0, 0);
	vertexBufferManager.AddData(1, 0, 0, 0);
	vertexBufferManager.AddData(1, 0, 0, 0);
	vertexBufferManager.AddData(1, 0, 0, 0);

	// texture
	const short NUMBER_OF_SIDES = 5;
	for (int i = 0; i < NUMBER_OF_SIDES; ++i)
	{
		vertexBufferManager.AddData(2, 0, 0);
		vertexBufferManager.AddData(2, 1, 0);
		vertexBufferManager.AddData(2, 0, 1);
		vertexBufferManager.AddData(2, 1, 1);
	}

	wallTextureID = TextureFromFile("texture_wall.jpg");
}

//
// Application's functions
//

Application::Application(void)
{
}

bool Application::onInitialize()
{
	//std::cout << "[onInitialize()] Start" << std::endl;

	// set the background color
	glClearColor(0.125f, 0.25f, 0.5f, 1.0f);

	glEnable(GL_DEPTH_TEST);

	// turn off back face and turn on lines for them
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_BACK, GL_LINE);

	// configure vertex buffer
	vertexBufferManager.AddAttribute(0, 3); // position
	vertexBufferManager.AddAttribute(1, 3); // normal
	vertexBufferManager.AddAttribute(2, 2); // texture

	// create geometries
	createQuad(vertexBufferManager, grassTextureID);
	createCuboid(vertexBufferManager, wallTextureID);
	vertexBufferManager.InitBuffers();

	// load shaders
	shaderManager.AttachShader(GL_VERTEX_SHADER, "vertex_shader.vert");
	shaderManager.AttachShader(GL_FRAGMENT_SHADER, "fragment_shader.frag");
	shaderManager.BindAttribLoc(0, "vs_in_position");
	shaderManager.BindAttribLoc(2, "vs_in_texture");
	if (!shaderManager.LinkProgram())
	{
		return false;
	}

	cameraManager.SetProj(45.0f, 640.0f / 480.0f, 0.01f, 1000.0f);

	//std::cout << "[onInitialize()] End" << std::endl;

	return true;
}