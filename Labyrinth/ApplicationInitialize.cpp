#include "Application.h"

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <set>

#include "config.h"
#include "GLUtils.hpp"

//
// Helper functions
//
 
int createQuad(gVertexBuffer * const &vertexBufferManager)
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

	return 4;
}

int createCuboid(gVertexBuffer * const &vertexBufferManager)
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

	return 20;
}

int createCylinderShield(gVertexBuffer * const &vertexBufferManager)
{
	const float offset = config::FIELD_SIZE / 2.0f;

	for (int i = 0; i <= config::COIN_RESOLUTION; ++i)
	{
		const float u0 = (i / (float)config::COIN_RESOLUTION);
		const float u = -u0 * 2 * 3.1415f;
		const float uCos = cosf(u);
		const float uSin = sinf(u);
		vertexBufferManager
			// position
			->AddData(0, 
				offset - config::COIN_THICKNESS,
				config::COIN_RADIUS * uCos - offset, 
				config::COIN_RADIUS * (uSin + 1))
			->AddData(0, 
				offset,
				config::COIN_RADIUS * uCos - offset, 
				config::COIN_RADIUS * (uSin + 1))
			// texture
			->AddData(2, u0, 0)
			->AddData(2, u0, 1);
	}

	return 2 * (config::COIN_RESOLUTION + 1);
}

int createCylinderTop(gVertexBuffer * const &vertexBufferManager)
{
	const float offset = config::FIELD_SIZE / 2.0f;

	vertexBufferManager
		->AddData(0, offset, -offset, config::COIN_RADIUS) // center position
		->AddData(2, 0.5f, 0.5f); // center texture
	for (float i = 0; i <= config::COIN_RESOLUTION; ++i)
	{
		const float u = (i / (float)config::COIN_RESOLUTION) * 2 * 3.1415f;
		const float uCos = cosf(u);
		const float uSin = sinf(u);
		vertexBufferManager
			// position
			->AddData(0,
			offset,
			config::COIN_RADIUS * uCos - offset,
			config::COIN_RADIUS * (uSin + 1))
			// texture
			->AddData(2, 0.5f * uCos + 0.5f, 0.5f * uSin + 0.5f);
	}

	return config::COIN_RESOLUTION + 2;
}

int createCylinderBottom(gVertexBuffer * const &vertexBufferManager)
{
	const float offset = config::FIELD_SIZE / 2.0f;

	vertexBufferManager
		->AddData(0, offset - config::COIN_THICKNESS, -offset, config::COIN_RADIUS) // center position
		->AddData(2, 0.5f, 0.5f); // center texture
	for (float i = 0; i <= config::COIN_RESOLUTION; ++i)
	{
		const float u = -(i / (float)config::COIN_RESOLUTION) * 2 * 3.1415f;
		const float uCos = cosf(u);
		const float uSin = sinf(u);
		vertexBufferManager
			// texture
			->AddData(0,
			offset - config::COIN_THICKNESS,
			config::COIN_RADIUS * uCos - offset,
			config::COIN_RADIUS * (uSin + 1))
			// position
			->AddData(2, 0.5f * uCos + 0.5f, 0.5f * uSin + 0.5f);
	}

	return config::COIN_RESOLUTION + 2;
}

int createTopPyramid(gVertexBuffer * const &vertexBufferManager) 
{
	vertexBufferManager
		->AddData(0, 0, config::DIAMOND_BOTTOM_HEIGHT + config::DIAMOND_TOP_HEIGHT, 0) // center position
		->AddData(2, 0.5f, 0.5f); // center texture
	for (float i = 0; i <= config::DIAMOND_NUMBER_OF_SIDES; ++i)
	{
		const float u = -(i / (float)config::DIAMOND_NUMBER_OF_SIDES) * 2 * 3.1415f;
		const float uCos = cosf(u);
		const float uSin = sinf(u);
		vertexBufferManager
			// position
			->AddData(0,
			config::DIAMOND_RADIUS * uCos,
			config::DIAMOND_BOTTOM_HEIGHT,
			config::DIAMOND_RADIUS * uSin)
			// texture
			->AddData(2, 0.5f * uCos + 0.5f, 0.5f * uSin + 0.5f);
	}

	return config::DIAMOND_NUMBER_OF_SIDES + 2;
}

int createBottomPyramid(gVertexBuffer * const &vertexBufferManager)
{
	vertexBufferManager
		->AddData(0, 0, 0, 0) // center position
		->AddData(2, 0.5f, 0.5f); // center texture
	for (float i = 0; i <= config::DIAMOND_NUMBER_OF_SIDES; ++i)
	{
		const float u = (i / (float)config::DIAMOND_NUMBER_OF_SIDES) * 2 * 3.1415f;
		const float uCos = cosf(u);
		const float uSin = sinf(u);
		vertexBufferManager
			// position
			->AddData(0,
			config::DIAMOND_RADIUS * uCos,
			config::DIAMOND_BOTTOM_HEIGHT,
			config::DIAMOND_RADIUS * uSin)
			// texture
			->AddData(2, 0.5f * uCos + 0.5f, 0.5f * uSin + 0.5f);
	}

	return config::DIAMOND_NUMBER_OF_SIDES + 2;
}

void initAndConfigFields(Field fields[config::MAP_SIZE][config::MAP_SIZE])
{
	srand(time(NULL));

	std::set<std::pair<short, short>> coinsPlace;
	while (coinsPlace.size() < config::NUMBER_OF_COINS)
	{
		const short i = rand() % config::MAP_SIZE;
		const short j = rand() % config::MAP_SIZE;
		if (coinsPlace.find(std::pair<short, short>(i, j)) == coinsPlace.end())
		{
			coinsPlace.insert(std::pair<short, short>(i, j));
		}
	}

	std::set<std::pair<short, short>> diamondsPlace;
	while (diamondsPlace.size() < config::NUMBER_OF_DIAMONDS)
	{
		const short i = rand() % config::MAP_SIZE;
		const short j = rand() % config::MAP_SIZE;
		if ((coinsPlace.find(std::pair<short, short>(i, j)) == coinsPlace.end())
				&& (diamondsPlace.find(std::pair<short, short>(i, j)) == diamondsPlace.end()))
		{
			diamondsPlace.insert(std::pair<short, short>(i, j));
		}
	}

	const short correctedPossibility = 1.0f / (config::WALL_POSSIBILITY / 2.0f);

	for (short i = 0; i < config::MAP_SIZE; ++i)
	{
		for (short j = 0; j < config::MAP_SIZE; ++j)
		{
			//
			// border
			//

			if (i == 0) fields[i][j].setIsOnLowerBorder(true);
			if (i == config::MAP_SIZE - 1) fields[i][j].setIsOnUpperBorder(true);
			if (j == 0) fields[i][j].setIsOnLeftBorder(true);
			if (j == config::MAP_SIZE - 1) fields[i][j].setIsOnRightBorder(true);

			//
			// wall
			//

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

			//
			// coin
			//

			if (coinsPlace.find(std::pair<short, short>(i, j)) != coinsPlace.end())
			{
				fields[i][j].setHasCoin(true);
			}

			//
			// diamond
			//

			if (diamondsPlace.find(std::pair<short, short>(i, j)) != diamondsPlace.end())
			{
				fields[i][j].setHasDiamond(true);
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
	
	//
	// create geometries
	//

	startOfQuadVertices = 0;
	numberOfQuadVertices = createQuad(&vertexBufferManager);

	startOfCuboidVertices = numberOfQuadVertices;
	numberOfCuboidVertices = createCuboid(&vertexBufferManager);

	startOfCylinderShieldVertices = startOfCuboidVertices + numberOfCuboidVertices;
	numberOfCylinderShieldVertices = createCylinderShield(&vertexBufferManager);

	startOfCylinderTopVertices = startOfCylinderShieldVertices + numberOfCylinderShieldVertices;
	numberOfCylinderTopVertices = createCylinderTop(&vertexBufferManager);

	startOfCylinderBottomVertices = startOfCylinderTopVertices + numberOfCylinderTopVertices;
	numberOfCylinderBottomVertices = createCylinderBottom(&vertexBufferManager);

	startOfTopPyramidVertices = startOfCylinderBottomVertices + numberOfCylinderBottomVertices;
	numberOfTopPyramidVertices = createTopPyramid(&vertexBufferManager);

	startOfBottomPyramidVertices = startOfTopPyramidVertices + numberOfTopPyramidVertices;
	numberOfBottomPyramidVertices = createBottomPyramid(&vertexBufferManager);

	vertexBufferManager.InitBuffers();

	// load textures
	grassTextureID = TextureFromFile("texture_grass.jpg");
	wallTextureID = TextureFromFile("texture_wall.jpg");
	coinTextureID = TextureFromFile("texture_coin.jpg");
	diamondTextureID = TextureFromFile("texture_diamond.jpg");

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