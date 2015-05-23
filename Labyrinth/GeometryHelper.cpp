#include "GeometryHelper.h"

#include "config.h"

//
// GeometryHelper
//

GeometryHelper::GeometryHelper(gVertexBuffer * const &vertexBufferManager) : vertexBufferManager(vertexBufferManager)
{
}

//
// QuadGeometryHelper
//

QuadGeometryHelper::QuadGeometryHelper(gVertexBuffer * const &vertexBufferManager) : GeometryHelper(vertexBufferManager)
{
}

void QuadGeometryHelper::initialize()
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

int QuadGeometryHelper::getTheNumberOfVerticies()
{
	return 4;
}

//
// CuboidGeometryHelper
//

CuboidGeometryHelper::CuboidGeometryHelper(gVertexBuffer * const &vertexBufferManager) : GeometryHelper(vertexBufferManager)
{
}

void CuboidGeometryHelper::initialize()
{
	//
	// position  
	//

	vertexBufferManager
		// upper side
		->AddData(0, config::FIELD_SIZE, config::WALL_HEIGHT, config::WALL_THICKNESS)
		->AddData(0, config::FIELD_SIZE, config::WALL_HEIGHT, 0)
		->AddData(0, 0, config::WALL_HEIGHT, 0)
		->AddData(0, 0, config::WALL_HEIGHT, config::WALL_THICKNESS)
		->AddData(1, 0, 1, 0)
		->AddData(1, 0, 1, 0)
		->AddData(1, 0, 1, 0)
		->AddData(1, 0, 1, 0)
		// height related 1. side
		->AddData(0, config::FIELD_SIZE, 0, config::WALL_THICKNESS)
		->AddData(0, config::FIELD_SIZE, config::WALL_HEIGHT, config::WALL_THICKNESS)
		->AddData(0, 0, config::WALL_HEIGHT, config::WALL_THICKNESS)
		->AddData(0, 0, 0, config::WALL_THICKNESS)
		->AddData(1, 0, 0, 1)
		->AddData(1, 0, 0, 1)
		->AddData(1, 0, 0, 1)
		->AddData(1, 0, 0, 1)
		// height related 2. side
		->AddData(0, 0, 0, 0)
		->AddData(0, 0, config::WALL_HEIGHT, 0)
		->AddData(0, config::FIELD_SIZE, config::WALL_HEIGHT, 0)
		->AddData(0, config::FIELD_SIZE, 0, 0)
		->AddData(1, 0, 0, -1)
		->AddData(1, 0, 0, -1)
		->AddData(1, 0, 0, -1)
		->AddData(1, 0, 0, -1)
		// thick related 1. side
		->AddData(0, 0, 0, config::WALL_THICKNESS)
		->AddData(0, 0, config::WALL_HEIGHT, config::WALL_THICKNESS)
		->AddData(0, 0, config::WALL_HEIGHT, 0)
		->AddData(0, 0, 0, 0)
		->AddData(1, -1, 0, 0)
		->AddData(1, -1, 0, 0)
		->AddData(1, -1, 0, 0)
		->AddData(1, -1, 0, 0)
		// thick related 2. side
		->AddData(0, config::FIELD_SIZE, 0, 0)
		->AddData(0, config::FIELD_SIZE, config::WALL_HEIGHT, 0)
		->AddData(0, config::FIELD_SIZE, config::WALL_HEIGHT, config::WALL_THICKNESS)
		->AddData(0, config::FIELD_SIZE, 0, config::WALL_THICKNESS)
		->AddData(1, 1, 0, 0)
		->AddData(1, 1, 0, 0)
		->AddData(1, 1, 0, 0)
		->AddData(1, 1, 0, 0);

	//
	// texture
	//

	const int NUMBER_OF_SIDES = 5;
	for (int i = 0; i < NUMBER_OF_SIDES; ++i)
	{
		vertexBufferManager
			->AddData(2, 0, 0)
			->AddData(2, 1, 0)
			->AddData(2, 0, 1)
			->AddData(2, 1, 1);
	}
}

int CuboidGeometryHelper::getTheNumberOfVerticies()
{
	return 20;
}


//
// SphereGeometryHelper
//

SphereGeometryHelper::SphereGeometryHelper(gVertexBuffer * const &vertexBufferManager) : GeometryHelper(vertexBufferManager)
{
}

// based on: http://stackoverflow.com/questions/22058111/opengl-draw-sphere-using-glvertex3f
void SphereGeometryHelper::initialize()
{
	for (int i = 0; i <= config::SUN_AND_MOON_RESOLUTION; ++i) {
		const float v0 = 3.1415f * (0.5f + (float)(i - 1) / config::SUN_AND_MOON_RESOLUTION);
		const float sinV0 = sinf(v0);
		const float cosV0 = cosf(v0);

		const float v1 = 3.1415f * (0.5f + (float)i / config::SUN_AND_MOON_RESOLUTION);
		const float sinV1 = sinf(v1);
		const float cosV1 = cosf(v1);

		for (int j = 0; j <= config::SUN_AND_MOON_RESOLUTION; ++j) {
			const float u = 2 * 3.1415f * (float)(j - 1) / config::SUN_AND_MOON_RESOLUTION;
			const float cosU = cosf(u);
			const float sinU = sinf(u);

			glm::vec3 firstNewVertex = glm::vec3(cosU * cosV0, sinU * cosV0, sinV0);
			glm::vec3 secondNewVertex = glm::vec3(cosU * cosV1, sinU * cosV1, sinV1);

			vertexBufferManager
				// position
				->AddData(0, firstNewVertex)
				->AddData(0, secondNewVertex)
				// normal
				->AddData(1, firstNewVertex)
				->AddData(1, secondNewVertex);
		}
	}
}

int SphereGeometryHelper::getTheNumberOfVerticies()
{
	return (config::SUN_AND_MOON_RESOLUTION + 1) * (config::SUN_AND_MOON_RESOLUTION + 1) * 2;
}


//
// CylinderGeometryHelper
//

CylinderGeometryHelper::CylinderGeometryHelper(gVertexBuffer * const &vertexBufferManager) : GeometryHelper(vertexBufferManager)
{
}

void CylinderGeometryHelper::initialize()
{
	initializeShield();
	initializeBottom();
	initializeTop();
}

void CylinderGeometryHelper::initializeShield()
{
	glm::vec3 lastVertex;

	const float halfThickness = config::COIN_THICKNESS / 2.0f;
	for (int i = 0; i <= config::COIN_RESOLUTION; ++i)
	{
		const float u0 = (i / (float)config::COIN_RESOLUTION);
		const float u = -u0 * 2 * 3.1415f;
		const float uCos = cosf(u);
		const float uSin = sinf(u);

		const glm::vec3 firstNewVertex = glm::vec3(-halfThickness, config::COIN_RADIUS * (uCos + 1), config::COIN_RADIUS * uSin);
		const glm::vec3 secondNewVertex = glm::vec3(halfThickness, config::COIN_RADIUS * (uCos + 1), config::COIN_RADIUS * uSin);

		vertexBufferManager
			// position
			->AddData(0, firstNewVertex.x, firstNewVertex.y, firstNewVertex.z)
			->AddData(0, secondNewVertex.x, secondNewVertex.y, secondNewVertex.z)
			// texture
			->AddData(2, u0, 0)
			->AddData(2, u0, 1);

		if (i == 0)
		{
			// normals will handle in the next iteration
			lastVertex = secondNewVertex;
			continue;
		}

		const glm::vec3 normal = -glm::cross(firstNewVertex - secondNewVertex, firstNewVertex - lastVertex);

		// normal
		if (i == 1)
		{
			vertexBufferManager
				->AddData(1, normal.x, normal.y, normal.z)
				->AddData(1, normal.x, normal.y, normal.z)
				->AddData(1, normal.x, normal.y, normal.z)
				->AddData(1, normal.x, normal.y, normal.z);
		}
		else
		{
			vertexBufferManager
				->AddData(1, normal.x, normal.y, normal.z)
				->AddData(1, normal.x, normal.y, normal.z);
		}

		lastVertex = secondNewVertex;
	}
}

void CylinderGeometryHelper::initializeBottom()
{
	const float halfThickness = config::COIN_THICKNESS / 2.0f;

	vertexBufferManager
		->AddData(0, -halfThickness, config::COIN_RADIUS, 0) // center position
		->AddData(1, -1, 0, 0) // center normal
		->AddData(2, 0.5f, 0.5f); // center texture
	for (int i = 0; i <= config::COIN_RESOLUTION; ++i)
	{
		const float u = -(i / (float)config::COIN_RESOLUTION) * 2 * 3.1415f;
		const float uCos = cosf(u);
		const float uSin = sinf(u);
		vertexBufferManager
			// texture
			->AddData(0,
			-halfThickness,
			config::COIN_RADIUS * (uCos + 1),
			config::COIN_RADIUS * uSin)
			// normal
			->AddData(1, -1, 0, 0)
			// position
			->AddData(2, 0.5f * uCos + 0.5f, 0.5f * uSin + 0.5f);
	}
}

void CylinderGeometryHelper::initializeTop()
{
	const float halfThickness = config::COIN_THICKNESS / 2.0f;

	vertexBufferManager
		->AddData(0, halfThickness, config::COIN_RADIUS, 0) // center position
		->AddData(1, 1, 0, 0) // center normal
		->AddData(2, 0.5f, 0.5f); // center texture
	for (int i = 0; i <= config::COIN_RESOLUTION; ++i)
	{
		const float u = (i / (float)config::COIN_RESOLUTION) * 2 * 3.1415f;
		const float uCos = cosf(u);
		const float uSin = sinf(u);
		vertexBufferManager
			// position
			->AddData(0,
			halfThickness,
			config::COIN_RADIUS * (uCos + 1),
			config::COIN_RADIUS * uSin)
			// normal
			->AddData(1, 1, 0, 0)
			// texture
			->AddData(2, 0.5f * uCos + 0.5f, 0.5f * uSin + 0.5f);
	}
}

int CylinderGeometryHelper::getTheNumberOfVerticies()
{
	return getTheNumberOfVerticiesForShield()
		+ getTheNumberOfVerticiesForBottom()
		+ getTheNumberOfVerticiesForTop();
}

int CylinderGeometryHelper::getTheNumberOfVerticiesForShield()
{
	return 2 * (config::COIN_RESOLUTION + 1);
}

int CylinderGeometryHelper::getTheNumberOfVerticiesForBottom()
{
	return config::COIN_RESOLUTION + 2;
}

int CylinderGeometryHelper::getTheNumberOfVerticiesForTop()
{
	return config::COIN_RESOLUTION + 2;
}

//
// DiamondGeometryHelper
//

DiamondGeometryHelper::DiamondGeometryHelper(gVertexBuffer * const &vertexBufferManager) : GeometryHelper(vertexBufferManager)
{
}

void DiamondGeometryHelper::initialize()
{
	initializeBottomPyramid();
	initializeTopPyramid();
}

void DiamondGeometryHelper::initializeBottomPyramid()
{
	const glm::vec3 bottomVertex = glm::vec3(0, 0, 0);
	glm::vec3 lastVertex;

	vertexBufferManager
		->AddData(0, bottomVertex.x, bottomVertex.y, bottomVertex.z) // center position
		->AddData(1, 0, -1, 0) // center normal
		->AddData(2, 0.5f, 0.5f); // center texture
	for (int i = 0; i <= config::DIAMOND_NUMBER_OF_SIDES; ++i)
	{
		const float u = (i / (float)config::DIAMOND_NUMBER_OF_SIDES) * 2 * 3.1415f;
		const float uCos = cosf(u);
		const float uSin = sinf(u);

		const glm::vec3 newVertex = glm::vec3(
			config::DIAMOND_RADIUS * uCos,
			config::DIAMOND_BOTTOM_HEIGHT,
			config::DIAMOND_RADIUS * uSin);

		vertexBufferManager
			// position
			->AddData(0, newVertex.x, newVertex.y, newVertex.z)
			// texture
			->AddData(2, 0.5f * uCos + 0.5f, 0.5f * uSin + 0.5f);

		if (i == 0)
		{
			// normals will handle in the next iteration
			lastVertex = newVertex;
			continue;
		}

		const glm::vec3 normal = -glm::cross(bottomVertex - newVertex, bottomVertex - lastVertex);

		if (i == 1)
		{
			vertexBufferManager
				->AddData(1, normal.x, normal.y, normal.z)
				->AddData(1, normal.x, normal.y, normal.z);
		}
		else
		{
			vertexBufferManager
				->AddData(1, normal.x, normal.y, normal.z);
		}

		lastVertex = newVertex;
	}
}

void DiamondGeometryHelper::initializeTopPyramid()
{
	const glm::vec3 topVertex = glm::vec3(0, config::DIAMOND_BOTTOM_HEIGHT + config::DIAMOND_TOP_HEIGHT, 0);
	glm::vec3 lastVertex;

	vertexBufferManager
		->AddData(0, topVertex.x, topVertex.y, topVertex.z) // center position
		->AddData(1, 0, 1, 0) // center normal
		->AddData(2, 0.5f, 0.5f); // center texture
	for (int i = 0; i <= config::DIAMOND_NUMBER_OF_SIDES; ++i)
	{
		const float u = -(i / (float)config::DIAMOND_NUMBER_OF_SIDES) * 2 * 3.1415f;
		const float uCos = cosf(u);
		const float uSin = sinf(u);

		const glm::vec3 newVertex = glm::vec3(
			config::DIAMOND_RADIUS * uCos,
			config::DIAMOND_BOTTOM_HEIGHT,
			config::DIAMOND_RADIUS * uSin);

		vertexBufferManager
			// position
			->AddData(0, newVertex.x, newVertex.y, newVertex.z)
			// texture
			->AddData(2, 0.5f * uCos + 0.5f, 0.5f * uSin + 0.5f);

		if (i == 0)
		{
			// normals will handle in the next iteration
			lastVertex = newVertex;
			continue;
		}

		const glm::vec3 normal = -glm::cross(topVertex - newVertex, topVertex - lastVertex);

		if (i == 1)
		{
			vertexBufferManager
				->AddData(1, normal.x, normal.y, normal.z)
				->AddData(1, normal.x, normal.y, normal.z);
		}
		else
		{
			vertexBufferManager
				->AddData(1, normal.x, normal.y, normal.z);
		}

		lastVertex = newVertex;
	}
}

int DiamondGeometryHelper::getTheNumberOfVerticies()
{
	return getTheNumberOfVerticiesForBottomPyramid()
		+ getTheNumberOfVerticiesForTopPyramid();
}

int DiamondGeometryHelper::getTheNumberOfVerticiesForBottomPyramid()
{
	return config::DIAMOND_NUMBER_OF_SIDES + 2;
}

int DiamondGeometryHelper::getTheNumberOfVerticiesForTopPyramid()
{
	return config::DIAMOND_NUMBER_OF_SIDES + 2;
}