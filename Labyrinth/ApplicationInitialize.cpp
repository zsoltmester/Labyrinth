#include "Application.h"

#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "config.h"
#include "GLUtils.hpp"

//
// Helper functions
//
 
void createQuad(gVertexBuffer * const &vertexBufferManager)
{
	vertexBufferManager
		// position
		->AddData(0, 0, 0, 0) // upper left
		->AddData(0, 0, 0, config::FIELD_SIZE) // lower left
		->AddData(0, config::FIELD_SIZE, 0, config::FIELD_SIZE) // lower right
		->AddData(0, config::FIELD_SIZE, 0, 0) // upper right
		// normal
		->AddData(1, 0, 1, 0)
		->AddData(1, 0, 1, 0)
		->AddData(1, 0, 1, 0)
		->AddData(1, 0, 1, 0)
		// texture
		->AddData(2, 0, 0)
		->AddData(2, 1, 0)
		->AddData(2, 0, 1)
		->AddData(2, 1, 1);
}

void createCuboid(gVertexBuffer * const &vertexBufferManager)
{
	//
	// position  
	//

	vertexBufferManager
		// upper side 
		->AddData(0, config::FIELD_SIZE, config::WALL_HEIGHT, config::WALL_THICKNESS)
		->AddData(0, config::FIELD_SIZE, config::WALL_HEIGHT,                      0)
		->AddData(0,                  0, config::WALL_HEIGHT,                      0)
		->AddData(0,                  0, config::WALL_HEIGHT, config::WALL_THICKNESS)
		// height related 1. side  												
		->AddData(0, config::FIELD_SIZE,                   0, config::WALL_THICKNESS)
		->AddData(0, config::FIELD_SIZE, config::WALL_HEIGHT, config::WALL_THICKNESS)
		->AddData(0,                  0, config::WALL_HEIGHT, config::WALL_THICKNESS)
		->AddData(0,                  0,                   0, config::WALL_THICKNESS)
		// height related 2. side												
		->AddData(0,                  0,                   0,                      0)
		->AddData(0,                  0, config::WALL_HEIGHT,                      0)
		->AddData(0, config::FIELD_SIZE, config::WALL_HEIGHT,                      0)
		->AddData(0, config::FIELD_SIZE,                   0,                      0)
		// thick related 1. side												
		->AddData(0,                  0,                   0, config::WALL_THICKNESS)
		->AddData(0,                  0, config::WALL_HEIGHT, config::WALL_THICKNESS)
		->AddData(0,                  0, config::WALL_HEIGHT,                      0)
		->AddData(0,                  0,                   0,                      0)
		// thick related 2. side												                     
		->AddData(0, config::FIELD_SIZE,                   0,                      0)
		->AddData(0, config::FIELD_SIZE, config::WALL_HEIGHT,                      0)
		->AddData(0, config::FIELD_SIZE, config::WALL_HEIGHT, config::WALL_THICKNESS)
		->AddData(0, config::FIELD_SIZE,                   0, config::WALL_THICKNESS);
	
	//
	// texture
	//

	const short NUMBER_OF_SIDES = 5;
	for (short i = 0; i < NUMBER_OF_SIDES; ++i)
	{
		vertexBufferManager
			->AddData(2, 0, 0)
			->AddData(2, 1, 0)
			->AddData(2, 0, 1)
			->AddData(2, 1, 1);
	}
}

void createCylinder(gVertexBuffer * const &vertexBufferManager)
{
	const float offset = config::FIELD_SIZE / 2.0f;

	//
	// shield
	//

	for (int i = 0; i <= config::COIN_RESOLUTION; ++i)
	{
		const float u0 = (i / (float)config::COIN_RESOLUTION);
		const float u = u0 * 2 * 3.1415f;
		const float uCos = cosf(u);
		const float uSin = sinf(u);
		vertexBufferManager
			// position
			->AddData(0, config::COIN_RADIUS * uCos + offset,                   0, config::COIN_RADIUS * uSin + offset)
			->AddData(0, config::COIN_RADIUS * uCos + offset, config::COIN_HEIGHT, config::COIN_RADIUS * uSin + offset)
			// texture
			->AddData(2, u0, 0)
			->AddData(2, u0, 1);
	}

	//
	// top circle
	//

	vertexBufferManager
		->AddData(0, offset, config::COIN_HEIGHT, offset) // center position
		->AddData(2, 0.5f, 0.5f); // center texture
	for (float i = 0; i <= config::COIN_RESOLUTION; ++i)
	{
		const float u = -(i / (float)config::COIN_RESOLUTION) * 2 * 3.1415f;
		const float uCos = cosf(u);
		const float uSin = sinf(u);
		vertexBufferManager
			// position
			->AddData(0, config::COIN_RADIUS * uCos + offset, config::COIN_HEIGHT, config::COIN_RADIUS * uSin + offset)
			// texture
			->AddData(2, 0.5f * uCos + 0.5f, 0.5f * uSin + 0.5f);
	}

	//
	// bottom circle
	//

	vertexBufferManager
		->AddData(0, offset, 0, offset) // center position
		->AddData(2, 0.5f, 0.5f); // center texture
	for (float i = 0; i <= config::COIN_RESOLUTION; ++i)
	{
		const float u = -(i / (float)config::COIN_RESOLUTION) * 2 * 3.1415f;
		const float uCos = cosf(u);
		const float uSin = sinf(u);
		vertexBufferManager
			// position
			->AddData(2, 0.5f * uCos + 0.5f, 0.5f * uSin + 0.5f)
			// texture
			->AddData(0, config::COIN_RADIUS * uCos + offset, 0, config::COIN_RADIUS * uSin + offset);
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
	vertexBufferManager
		.AddAttribute(0, 3) // position
		->AddAttribute(1, 3) // normal
		->AddAttribute(2, 2); // texture

	// create geometries
	createQuad(&vertexBufferManager);
	createCuboid(&vertexBufferManager);
	createCylinder(&vertexBufferManager);
	vertexBufferManager.InitBuffers();

	// load textures
	grassTextureID = TextureFromFile("texture_grass.jpg");
	wallTextureID = TextureFromFile("texture_wall.jpg");
	coinTextureID = TextureFromFile("texture_coin.jpg");

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