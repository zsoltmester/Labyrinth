#pragma once

namespace config
{
	const bool	IS_DEBUG = true;

	const short	MAP_SIZE = 10;

	const float	QUAD_SIDE = 1.0f;
	const float	WALL_HEIGHT = QUAD_SIDE * 1.25f;
	const float	WALL_THICKNESS = QUAD_SIDE *  0.1f;

	// is has to be greater than 1
	const float WALL_POSSIBILITY = 0.5f;
}