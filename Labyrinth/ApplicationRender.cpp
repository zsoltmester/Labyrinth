#include "Application.h"

#include <iostream>

#include "config.h"

void Application::drawWall(const glm::mat4 matWorld)
{
	glm::mat4 mvp = cameraManager.GetViewProj() * matWorld;
	shaderManager.SetUniform("MVP", mvp);
	shaderManager.SetTexture("texture_image", 0, wallTextureID);

	vertexBufferManager.Draw(GL_QUADS, 4, 20);
}

void Application::onRender()
{
	//std::cout << "[onRender()] Start" << std::endl;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shaderManager.On();
	vertexBufferManager.On();

	glm::mat4 matWorld;
	glm::mat4 mvp;

	// draw the fields
	for (short i = 0; i < config::MAP_SIZE; ++i) 
	{
		for (short j = 0; j < config::MAP_SIZE; ++j) 
		{
			const glm::mat4 translateToCurrent 
				= glm::translate<float>(i * config::FIELD_SIZE, 0, j * config::FIELD_SIZE);

			// the grass
			mvp = cameraManager.GetViewProj() * translateToCurrent;
			shaderManager.SetUniform("MVP", mvp);
			shaderManager.SetTexture("texture_image", 0, grassTextureID);
			vertexBufferManager.Draw(GL_QUADS, 0, 4);

			if (fields[i][j].hasCoin())
			{
				// TODO
				vertexBufferManager.Draw(GL_QUAD_STRIP, 24, 2 * (config::COIN_RESOLUTION + 1));
				vertexBufferManager.Draw(GL_TRIANGLE_FAN, 24 + 2 * (config::COIN_RESOLUTION + 1), config::COIN_RESOLUTION + 2);
				vertexBufferManager.Draw(GL_TRIANGLE_FAN, 24 + 2 * (config::COIN_RESOLUTION + 1) + config::COIN_RESOLUTION + 2, config::COIN_RESOLUTION + 2);
			}

			//
			// the walls
			//

			if (fields[i][j].hasLeftWall())
			{
				drawWall(translateToCurrent);
			}

			if (fields[i][j].hasRightWall())
			{
				matWorld = translateToCurrent 
					* glm::translate<float>(0, 0, config::FIELD_SIZE - config::WALL_THICKNESS);
				drawWall(matWorld);
			}

			if (fields[i][j].hasUpperWall())
			{
				matWorld = translateToCurrent
					* glm::translate<float>(config::FIELD_SIZE, 0, 0)
					* glm::rotate<float>(-90, 0, 1, 0);
				drawWall(matWorld);
			}

			if (fields[i][j].hasLowerWall())
			{
				matWorld = translateToCurrent
					* glm::translate<float>(config::WALL_THICKNESS, 0, 0)
					* glm::rotate<float>(-90, 0, 1, 0);
				drawWall(matWorld);
			}

		}
	}

	vertexBufferManager.Off();
	shaderManager.Off();

	//std::cout << "[onRender()] End" << std::endl;
}