#include "Application.h"

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <set>

#include "config.h"
#include "GeometryHelper.h"
#include "GLUtils.hpp"

//
// Helper functions
//

void initAndConfigFields(Field fields[config::MAP_SIZE][config::MAP_SIZE])
{
	srand(time(NULL));
	short i;
	short j;
	
	// coins place
	std::set<std::pair<short, short>> coinsPlace;
	while (coinsPlace.size() < config::NUMBER_OF_COINS)
	{
		i = rand() % config::MAP_SIZE;
		j = rand() % config::MAP_SIZE;
		if (coinsPlace.find(std::pair<short, short>(i, j)) == coinsPlace.end())
		{
			coinsPlace.insert(std::pair<short, short>(i, j));
		}
	}

	// diamonds place
	std::set<std::pair<short, short>> diamondsPlace;
	while (diamondsPlace.size() < config::NUMBER_OF_DIAMONDS)
	{
		i = rand() % config::MAP_SIZE;
		j = rand() % config::MAP_SIZE;
		if ((coinsPlace.find(std::pair<short, short>(i, j)) == coinsPlace.end())
				&& (diamondsPlace.find(std::pair<short, short>(i, j)) == diamondsPlace.end()))
		{
			diamondsPlace.insert(std::pair<short, short>(i, j));
		}
	}

	// start portal place
	std::pair<short, short> startPortalPlace;
	do
	{
		i = rand() % config::MAP_SIZE;
		j = rand() % config::MAP_SIZE;
	} while ((coinsPlace.find(std::pair<short, short>(i, j)) != coinsPlace.end())
		|| (diamondsPlace.find(std::pair<short, short>(i, j)) != diamondsPlace.end()));
	startPortalPlace = std::pair<short, short>(i, j);
	
	// end portal place
	std::pair<short, short> endPortalPlace;
	do
	{
		i = rand() % config::MAP_SIZE;
		j = rand() % config::MAP_SIZE;
	} while ((coinsPlace.find(std::pair<short, short>(i, j)) != coinsPlace.end())
		|| (diamondsPlace.find(std::pair<short, short>(i, j)) != diamondsPlace.end())
		|| startPortalPlace == endPortalPlace);
	endPortalPlace = std::pair<short, short>(i, j);

	// set fields attributes
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
				if (config::WITH_DOUBLE_WALL && !fields[i][j].isOnLeftBorder()) fields[i][j - 1].setHasRightWall(true);
			}

			if (!fields[i][j].hasRightWall() && rand() % correctedPossibility == 0)
			{
				fields[i][j].setHasRightWall(true);
				if (config::WITH_DOUBLE_WALL && !fields[i][j].isOnRightBorder()) fields[i][j + 1].setHasLeftWall(true);
			}

			if (!fields[i][j].hasUpperWall() && rand() % correctedPossibility == 0)
			{
				fields[i][j].setHasUpperWall(true);
				if (config::WITH_DOUBLE_WALL && !fields[i][j].isOnUpperBorder()) fields[i + 1][j].setHasLowerWall(true);
			}
			
			if (!fields[i][j].hasLowerWall() && rand() % correctedPossibility == 0)
			{
				fields[i][j].setHasLowerWall(true);
				if (config::WITH_DOUBLE_WALL && !fields[i][j].isOnLowerBorder()) fields[i - 1][j].setHasUpperWall(true);
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

			//
			// portal
			//

			if (startPortalPlace == std::pair<short, short>(i, j))
			{
				fields[i][j].setHasPortal(Field::PortalType::START);
			} 
			else if (endPortalPlace == std::pair<short, short>(i, j))
			{
				fields[i][j].setHasPortal(Field::PortalType::END);
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

	cameraManager.SetProj(45.0f, config::SCREEN_RESOLUTION_WIDTH / (float)config::SCREEN_RESOLUTION_HEIGHT, 0.01f, 1000.0f);

	initAndConfigFields(fields);

	//std::cout << "[onInitialize()] End" << std::endl;

	return true;
}