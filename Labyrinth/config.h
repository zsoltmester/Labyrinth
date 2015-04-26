#pragma once

namespace config
{
	const bool	IS_DEBUG = true;

	const short	MAP_SIZE = 10;

	const float	FIELD_SIZE = 1.0f;

	const float	WALL_HEIGHT = FIELD_SIZE * 1.25f;
	const float	WALL_THICKNESS = FIELD_SIZE *  0.1f;
	// is has to be greater than 1
	const float WALL_POSSIBILITY = 0.5f;

	const float COIN_RADIUS = 0.25f;
	const float COIN_THICKNESS = 0.1f;
	const float COIN_ANIMATION_LENGTH = 5;
	// the coin's shield will build up with N cuboid
	// and the top and bottom circles with N triangle
	const short COIN_RESOLUTION = 20;
	const short NUMBER_OF_COINS = 10;

	const float DIAMOND_BOTTOM_HEIGHT = 0.75f;
	const float DIAMOND_TOP_HEIGHT = DIAMOND_BOTTOM_HEIGHT / 2.0f;
	const float DIAMOND_RADIUS = 0.25f;
	const float DIAMOND_NUMBER_OF_SIDES = 6;
	const float DIAMOND_ANIMATION_LENGTH = 5;
	const float NUMBER_OF_DIAMONDS = 5;
}