#pragma once

#include <iostream>

namespace config
{
	const bool	IS_DEBUG = true;

	const short SCREEN_RESOLUTION_WIDTH = 1366;
	const short SCREEN_RESOLUTION_HEIGHT = 768;

	const short	MAP_SIZE = 10; // in task: 50

	const std::string TEXTURE_FILE_NAME_GRASS = "texture_grass.bmp";
	const std::string TEXTURE_FILE_NAME_WALL = "texture_wall.bmp";
	const std::string TEXTURE_FILE_NAME_COIN = "texture_coin.bmp";
	const std::string TEXTURE_FILE_NAME_DIAMOND = "texture_diamond.bmp";

	const float	FIELD_SIZE = 1.0f;
	const float	WALL_HEIGHT = FIELD_SIZE * 1.25f;
	const float	WALL_THICKNESS = FIELD_SIZE *  0.1f;
	const float WALL_POSSIBILITY = 0.5f;

	const float COIN_RADIUS = 0.25f;
	const float COIN_THICKNESS = 0.1f;
	const float COIN_ANIMATION_LENGTH = 5;
	// the coin's shield will build up with N cuboid
	// and the top and bottom circles with N triangle
	const short COIN_RESOLUTION = 20;
	const short NUMBER_OF_COINS = 20; // in task: 100

	const float DIAMOND_BOTTOM_HEIGHT = 0.75f;
	const float DIAMOND_TOP_HEIGHT = DIAMOND_BOTTOM_HEIGHT / 2.0f;
	const float DIAMOND_RADIUS = 0.25f;
	const float DIAMOND_NUMBER_OF_SIDES = 6;
	const float DIAMOND_ANIMATION_LENGTH = 5;
	const float NUMBER_OF_DIAMONDS = 4; // in task: 10

	const short SUN_AND_MOON_RESOLUTION = 20;
	const float SUN_AND_MOON_SIZE = 0.25f;
	const float SUN_AND_MOON_ORBIT_RADIUS_MULTIPLIER = 1.1f;
	const float SUN_AND_MOON_ANIMATION_LENGTH = 10.0f;
}