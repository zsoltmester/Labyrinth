#include "Application.h"

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <set>

#include "GLUtils.hpp"
#include "ObjParser_OGL3.h"

#include "config.h"
#include "GeometryHelper.h"

//
// Helper functions
//

void initAndConfigFields(Field fields[config::MAP_SIZE][config::MAP_SIZE])
{
	srand(time(NULL));
	int i;
	int j;

	// coins place
	std::set<std::pair<int, int>> coinsPlace;
	while (coinsPlace.size() < config::NUMBER_OF_COINS)
	{
		i = rand() % config::MAP_SIZE;
		j = rand() % config::MAP_SIZE;
		if (coinsPlace.find(std::pair<int, int>(i, j)) == coinsPlace.end())
		{
			coinsPlace.insert(std::pair<int, int>(i, j));
		}
	}

	// diamonds place
	std::set<std::pair<int, int>> diamondsPlace;
	while (diamondsPlace.size() < config::NUMBER_OF_DIAMONDS)
	{
		i = rand() % config::MAP_SIZE;
		j = rand() % config::MAP_SIZE;
		if ((coinsPlace.find(std::pair<int, int>(i, j)) == coinsPlace.end())
			&& (diamondsPlace.find(std::pair<int, int>(i, j)) == diamondsPlace.end()))
		{
			diamondsPlace.insert(std::pair<int, int>(i, j));
		}
	}

	// first portal place
	std::pair<int, int> firstPortalPlace;
	do
	{
		i = rand() % config::MAP_SIZE;
		j = rand() % config::MAP_SIZE;
		firstPortalPlace = std::pair<int, int>(i, j);
	} while ((coinsPlace.find(firstPortalPlace) != coinsPlace.end())
		|| (diamondsPlace.find(firstPortalPlace) != diamondsPlace.end()));

	// second portal place
	std::pair<int, int> secondPortalPlace;
	do
	{
		i = rand() % config::MAP_SIZE;
		j = rand() % config::MAP_SIZE;
		secondPortalPlace = std::pair<int, int>(i, j);
	} while ((coinsPlace.find(secondPortalPlace) != coinsPlace.end())
		|| (diamondsPlace.find(secondPortalPlace) != diamondsPlace.end())
		|| firstPortalPlace == secondPortalPlace);

	// set fields attributes
	const int correctedPossibility = 1.0f / (config::WALL_POSSIBILITY / 2.0f);
	for (int i = 0; i < config::MAP_SIZE; ++i)
	{
		for (int j = 0; j < config::MAP_SIZE; ++j)
		{
			//
			// border
			//

			if (i == 0) fields[i][j].setIsOnXMinusBorder(true);
			if (i == config::MAP_SIZE - 1) fields[i][j].setIsOnXPlusBorder(true);
			if (j == 0) fields[i][j].setIsOnZMinusBorder(true);
			if (j == config::MAP_SIZE - 1) fields[i][j].setIsOnZPlusBorder(true);

			//
			// wall
			//

			if (!fields[i][j].hasZMinusWall() && rand() % correctedPossibility == 0)
			{
				fields[i][j].setHasZMinusWall(true);
				if (config::WITH_DOUBLE_WALL && !fields[i][j].isOnZMinusBorder())
				{
					fields[i][j - 1].setHasZPlusWall(true);
				}
			}

			if (!fields[i][j].hasZPlusWall() && rand() % correctedPossibility == 0)
			{
				fields[i][j].setHasZPlusWall(true);
				if (config::WITH_DOUBLE_WALL && !fields[i][j].isOnZPlusBorder())
				{
					fields[i][j + 1].setHasZMinusWall(true);
				}
			}

			if (!fields[i][j].hasXPlusWall() && rand() % correctedPossibility == 0)
			{
				fields[i][j].setHasXPlusWall(true);
				if (config::WITH_DOUBLE_WALL && !fields[i][j].isOnXPlusBorder())
				{
					fields[i + 1][j].setHasXMinusWall(true);
				}
			}

			if (!fields[i][j].hasXMinusWall() && rand() % correctedPossibility == 0)
			{
				fields[i][j].setHasXMinusWall(true);
				if (config::WITH_DOUBLE_WALL && !fields[i][j].isOnXMinusBorder())
				{
					fields[i - 1][j].setHasXPlusWall(true);
				}
			}

			//
			// coin
			//

			if (coinsPlace.find(std::pair<int, int>(i, j)) != coinsPlace.end())
			{
				fields[i][j].setHasCoin(true);
			}

			//
			// diamond
			//

			if (diamondsPlace.find(std::pair<int, int>(i, j)) != diamondsPlace.end())
			{
				fields[i][j].setHasDiamond(true);
			}

			//
			// portal
			//

			if (firstPortalPlace == std::pair<int, int>(i, j))
			{
				fields[i][j].setHasPortal(true);
			}
			else if (secondPortalPlace == std::pair<int, int>(i, j))
			{
				fields[i][j].setHasPortal(true);
			}
		}
	}
}

void initHero(Hero*& hero, const Field fields[config::MAP_SIZE][config::MAP_SIZE])
{
	int i, j;

	// hero position
	do
	{
		i = rand() % config::MAP_SIZE;
		j = rand() % config::MAP_SIZE;
	} while (fields[i][j].hasCoin()
		|| fields[i][j].hasDiamond()
		|| fields[i][j].hasPortal()
		|| fields[i][j].hasPortal());
	Character::Position heroPosition = Character::Position(i, j);

	// hero direction
	i = rand() % 4;
	Character::Direction heroDirection;
	switch (i)
	{
	case 0:
		heroDirection = Character::Direction::X_PLUS;
		break;
	case 1:
		heroDirection = Character::Direction::X_MINUS;
		break;
	case 2:
		heroDirection = Character::Direction::Z_PLUS;
		break;
	case 3:
		heroDirection = Character::Direction::Z_MINUS;
		break;
	}

	hero = new Hero(heroPosition, heroDirection);
}

//
// Application's functions
//

Application::Application(void)
{
	isTopView = false;
	collectedCoins = 0;
	collectedDiamonds = 0;
	isPortalActive = true;
	isWin = false;
	winLastRenderingTime = 0;
	xWinFunctionParameter = 0;
	isGameOver = false;
	gameOverLastRenderingTime = 0;
	xGameOverFunctionParameter = 0;
}

const bool Application::onInitialize()
{
	//std::cout << "[onInitialize()] Start" << std::endl;

	// set the background color
	glClearColor(0.125f, 0.25f, 0.5f, 1.0f);

	glEnable(GL_DEPTH_TEST);

	// turn off back face
	glEnable(GL_CULL_FACE);

	// configure vertex buffer
	vertexBufferManager
		.AddAttribute(0, 3) // position
		->AddAttribute(1, 3) // normal
		->AddAttribute(2, 2); // texture

	//
	// create geometries
	//

	// quad
	GeometryHelper* geometryHelper = new QuadGeometryHelper(&vertexBufferManager);
	geometryHelper->initialize();
	startOfQuadVertices = 0;
	numberOfQuadVertices = geometryHelper->getTheNumberOfVerticies();
	delete geometryHelper;

	// cuboid
	geometryHelper = new CuboidGeometryHelper(&vertexBufferManager);
	geometryHelper->initialize();
	startOfCuboidVertices = numberOfQuadVertices;
	numberOfCuboidVertices = geometryHelper->getTheNumberOfVerticies();
	delete geometryHelper;

	// cylinder
	CylinderGeometryHelper* cylinderGeometryHelper = new CylinderGeometryHelper(&vertexBufferManager);
	cylinderGeometryHelper->initialize();

	startOfCylinderShieldVertices = startOfCuboidVertices + numberOfCuboidVertices;
	numberOfCylinderShieldVertices = cylinderGeometryHelper->getTheNumberOfVerticiesForShield();

	startOfCylinderBottomVertices = startOfCylinderShieldVertices + numberOfCylinderShieldVertices;
	numberOfCylinderBottomVertices = cylinderGeometryHelper->getTheNumberOfVerticiesForBottom();

	startOfCylinderTopVertices = startOfCylinderBottomVertices + numberOfCylinderBottomVertices;
	numberOfCylinderTopVertices = cylinderGeometryHelper->getTheNumberOfVerticiesForTop();

	delete cylinderGeometryHelper;

	// diamond
	DiamondGeometryHelper* diamondGeometryHelper = new DiamondGeometryHelper(&vertexBufferManager);
	diamondGeometryHelper->initialize();

	startOfBottomPyramidVertices = startOfCylinderTopVertices + numberOfCylinderTopVertices;
	numberOfBottomPyramidVertices = diamondGeometryHelper->getTheNumberOfVerticiesForBottomPyramid();

	startOfTopPyramidVertices = startOfBottomPyramidVertices + numberOfBottomPyramidVertices;
	numberOfTopPyramidVertices = diamondGeometryHelper->getTheNumberOfVerticiesForTopPyramid();

	delete diamondGeometryHelper;

	// sphere
	geometryHelper = new SphereGeometryHelper(&vertexBufferManager);
	startOfSphereVertices = startOfTopPyramidVertices + numberOfTopPyramidVertices;
	geometryHelper->initialize();
	numberOfSphereVertices = geometryHelper->getTheNumberOfVerticies();
	delete geometryHelper;

	vertexBufferManager.InitBuffers();

	//
	// load textures
	//

	grassTextureID = TextureFromFile(config::TEXTURE_FILE_NAME_GRASS.c_str());
	wallTextureID = TextureFromFile(config::TEXTURE_FILE_NAME_WALL.c_str());
	coinTextureID = TextureFromFile(config::TEXTURE_FILE_NAME_COIN.c_str());
	diamondTextureID = TextureFromFile(config::TEXTURE_FILE_NAME_DIAMOND.c_str());
	suzanneTextureID = TextureFromFile(config::TEXTURE_FILE_NAME_SUZANNE.c_str());

	//
	// init shaders
	//

	shaderManager.AttachShader(GL_VERTEX_SHADER, "vertex_shader.vert");
	shaderManager.AttachShader(GL_FRAGMENT_SHADER, "fragment_shader.frag");
	shaderManager.BindAttribLoc(0, "vs_in_position");
	shaderManager.BindAttribLoc(1, "vs_in_normal");
	shaderManager.BindAttribLoc(2, "vs_in_texture");

	if (!shaderManager.LinkProgram())
	{
		return false;
	}

	shaderManager.On();
	shaderManager.SetUniform("ambientLightColor", config::AMBIENT_LIGHT_COLOR);
	shaderManager.SetUniform("ambientLightStrength", config::AMBIENT_LIGHT_STRENGTH);
	shaderManager.SetUniform("sunDiffuseLightColor", config::SUN_DIFFUSE_LIGHT_COLOR);
	shaderManager.SetUniform("sunSpecularLightColor", config::SUN_SPECULAR_LIGHT_COLOR);
	shaderManager.SetUniform("moonDiffuseLightColor", config::MOON_DIFFUSE_LIGHT_COLOR);
	shaderManager.SetUniform("moonSpecularLightColor", config::MOON_SPECULAR_LIGHT_COLOR);
	shaderManager.SetUniform("specularLightStrength", config::SPECULAR_LIGHT_STRENGTH);
	shaderManager.SetUniform("specularLightSize", config::SPECULAR_LIGHT_SIZE);
	shaderManager.Off();

	//
	// init mesh
	//

	heroMesh = ObjParser::parse("Suzanne.obj");
	heroMesh->initBuffers();

	//
	//  other initialization
	//

	cameraManager.SetProj(45.0f, config::SCREEN_RESOLUTION_WIDTH / (float)config::SCREEN_RESOLUTION_HEIGHT, 0.01f, 1000.0f);

	initAndConfigFields(fields);
	initHero(hero, fields);

	//std::cout << "[onInitialize()] End" << std::endl;

	return true;
}