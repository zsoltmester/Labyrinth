#include "Application.h"

#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "config.h"
#include "GLUtils.hpp"

//
// Helper functions
//
 
void createQuad(gVertexBuffer &vertexBufferManager, GLuint &grassTextureID)
{
	// position                                     x  y                  z
	vertexBufferManager.AddData(0,                  0, 0,                  0); // upper left
	vertexBufferManager.AddData(0,                  0, 0, config::FIELD_SIZE); // lower left
	vertexBufferManager.AddData(0, config::FIELD_SIZE, 0, config::FIELD_SIZE); // lower right
	vertexBufferManager.AddData(0, config::FIELD_SIZE, 0,                  0); // upper right

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

	// upper side                                   x                    y                       z
	vertexBufferManager.AddData(0, config::FIELD_SIZE, config::WALL_HEIGHT, config::WALL_THICKNESS);
	vertexBufferManager.AddData(0, config::FIELD_SIZE, config::WALL_HEIGHT,                      0);
	vertexBufferManager.AddData(0,                  0, config::WALL_HEIGHT,                      0);
	vertexBufferManager.AddData(0,                  0, config::WALL_HEIGHT, config::WALL_THICKNESS);
	// height related 1. side  												
	vertexBufferManager.AddData(0, config::FIELD_SIZE,                   0, config::WALL_THICKNESS);
	vertexBufferManager.AddData(0, config::FIELD_SIZE, config::WALL_HEIGHT, config::WALL_THICKNESS);
	vertexBufferManager.AddData(0,                  0, config::WALL_HEIGHT, config::WALL_THICKNESS);
	vertexBufferManager.AddData(0,                  0,                   0, config::WALL_THICKNESS);
	// height related 2. side												
	vertexBufferManager.AddData(0,                  0,                   0,                      0);
	vertexBufferManager.AddData(0,                  0, config::WALL_HEIGHT,                      0);
	vertexBufferManager.AddData(0, config::FIELD_SIZE, config::WALL_HEIGHT,                      0);
	vertexBufferManager.AddData(0, config::FIELD_SIZE,                   0,                      0);
	// thick related 1. side												
	vertexBufferManager.AddData(0,                  0,                   0, config::WALL_THICKNESS);
	vertexBufferManager.AddData(0,                  0, config::WALL_HEIGHT, config::WALL_THICKNESS);
	vertexBufferManager.AddData(0,                  0, config::WALL_HEIGHT,                      0);
	vertexBufferManager.AddData(0,                  0,                   0,                      0);
	// thick related 2. side												                     
	vertexBufferManager.AddData(0, config::FIELD_SIZE,                   0,                      0);
	vertexBufferManager.AddData(0, config::FIELD_SIZE, config::WALL_HEIGHT,                      0);
	vertexBufferManager.AddData(0, config::FIELD_SIZE, config::WALL_HEIGHT, config::WALL_THICKNESS);
	vertexBufferManager.AddData(0, config::FIELD_SIZE,                   0, config::WALL_THICKNESS);

	// texture
	const short NUMBER_OF_SIDES = 5;
	for (short i = 0; i < NUMBER_OF_SIDES; ++i)
	{
		vertexBufferManager.AddData(2, 0, 0);
		vertexBufferManager.AddData(2, 1, 0);
		vertexBufferManager.AddData(2, 0, 1);
		vertexBufferManager.AddData(2, 1, 1);
	}

	wallTextureID = TextureFromFile("texture_wall.jpg");
}

void createCylinder(gVertexBuffer &vertexBufferManager)
{
	const float offset = (config::FIELD_SIZE / 2.0f);

	//
	// shield
	//

	for (int i = 0; i <= config::COIN_RESOLUTION; ++i)
	{
		const float u = (i / (float) config::COIN_RESOLUTION) * (2 * 3.1415f);
		// position
		vertexBufferManager
			.AddData(0, config::COIN_RADIUS * cosf(u) + offset, 0, config::COIN_RADIUS * sinf(u) + offset);
		vertexBufferManager
			.AddData(0, config::COIN_RADIUS * cosf(u) + offset, config::COIN_HEIGHT, config::COIN_RADIUS * sinf(u) + offset);
		// texture
		vertexBufferManager.AddData(2, (i / (float)config::COIN_RESOLUTION), 0);
		vertexBufferManager.AddData(2, (i / (float)config::COIN_RESOLUTION), 1);
	}

	//
	// top circle
	//

	vertexBufferManager.AddData(0, 0 + offset, config::COIN_HEIGHT, offset);  // center position
	vertexBufferManager.AddData(2, 0.5f, 0.5f); // center texture
	for (float i = 0; i <= config::COIN_RESOLUTION; ++i)
	{
		const float u = -(i / (float)config::COIN_RESOLUTION) * 2 * 3.1415f;
		// position
		vertexBufferManager.AddData(0, config::COIN_RADIUS * cosf(u) + offset, config::COIN_HEIGHT, config::COIN_RADIUS * sinf(u) + offset);
		// texture
		vertexBufferManager.AddData(2, 0.5f * cosf(u) + 0.5f, 0.5f * sinf(u) + 0.5f);
	}

	//
	// bottom circle
	//

	vertexBufferManager.AddData(0, 0 + offset, 0, 0 + offset); // center position
	vertexBufferManager.AddData(2, 0.5f, 0.5f); // center texture
	for (float i = 0; i <= config::COIN_RESOLUTION; ++i)
	{
		const float u = (i / (float)config::COIN_RESOLUTION) * 2 * 3.1415f;
		// position
		vertexBufferManager.AddData(2, 0.5f * cosf(u) + 0.5f, 0.5f * sinf(u) + 0.5f);
		// texture
		vertexBufferManager.AddData(0, config::COIN_RADIUS * cosf(u) + offset, 0, config::COIN_RADIUS * sinf(u) + offset);
	}
}

void initAndConfigFields(Field fields[config::MAP_SIZE][config::MAP_SIZE])
{
	srand(time(NULL));

	const short correctedPossibility = 1.0f / (config::WALL_POSSIBILITY / 2.0f);

	for (short i = 0; i < config::MAP_SIZE; ++i)
	{
		for (short j = 0; j < config::MAP_SIZE; ++j)
		{
			if (i == 0)						fields[i][j].setIsOnLowerBorder(true);
			if (i == config::MAP_SIZE - 1)	fields[i][j].setIsOnUpperBorder(true);
			if (j == 0)						fields[i][j].setIsOnLeftBorder(true);
			if (j == config::MAP_SIZE - 1)	fields[i][j].setIsOnRightBorder(true);

			if (!fields[i][j].hasLeftWall() && rand() % correctedPossibility == 0)
			{
				fields[i][j].setHasLeftWall(true);
				if (!fields[i][j].isOnLeftBorder()) fields[i][j - 1].setHasRightWall(true);
			}

			if (!fields[i][j].hasRightWall() && rand() % correctedPossibility == 0)
			{
				fields[i][j].setHasRightWall(true);
				if (!fields[i][j].isOnRightBorder()) fields[i][j + 1].setHasLeftWall(true);
			}

			if (!fields[i][j].hasUpperWall() && rand() % correctedPossibility == 0)
			{
				fields[i][j].setHasUpperWall(true);
				if (!fields[i][j].isOnUpperBorder()) fields[i + 1][j].setHasLowerWall(true);
			}
			
			if (!fields[i][j].hasLowerWall() && rand() % correctedPossibility == 0)
			{
				fields[i][j].setHasLowerWall(true);
				if (!fields[i][j].isOnLowerBorder()) fields[i - 1][j].setHasUpperWall(true);
			}
		}
	}

}

//
// Application's functions
//

Application::Application(void)
{ 
}

const bool Application::onInitialize()
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
	createCylinder(vertexBufferManager);
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

	initAndConfigFields(fields);

	//std::cout << "[onInitialize()] End" << std::endl;

	return true;
}