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
	const float COIN_HEIGHT = 1;
	// the coin's shield will build up with N cuboid
	// and the top and bottom circles with N triangle
	static const short COIN_RESOLUTION = 20;
}