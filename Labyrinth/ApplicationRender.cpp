#include "Application.h"

#include <iostream>

#include "config.h"

void Application::drawWall(const glm::mat4 matWorld)
{
	glm::mat4 mvp = cameraManager.GetViewProj() * matWorld;
	shaderManager.SetUniform("MVP", mvp);
	shaderManager.SetTexture("texture_image", 0, wallTextureID);

	vertexBufferManager.Draw(GL_QUADS, startOfCuboidVertices, numberOfCuboidVertices);
}

void Application::onRender()
{
	//std::cout << "[onRender()] Start" << std::endl;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shaderManager.On();
	vertexBufferManager.On();

	shaderManager.SetUniform("isTheSunOrTheMoon", 0);

	glm::mat4 matWorld;
	glm::mat4 mvp;

	//
	// draw the fields
	//
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
			vertexBufferManager.Draw(GL_QUADS, startOfQuadVertices, numberOfQuadVertices);

			if (fields[i][j].hasCoin())
			{
				const float coinRotation = SDL_GetTicks() / 1000.0f * 360.0f / config::COIN_ANIMATION_LENGTH;
				const float offset = config::FIELD_SIZE / 2.0f;

				matWorld = translateToCurrent
					* glm::translate<float>(offset - config::COIN_THICKNESS / 2.0f, 0, offset) // translate back from the origin
					* glm::rotate<float>(coinRotation, 0, 1, 0) // for animation
					* glm::translate<float>(config::COIN_THICKNESS / 2.0f - offset, 0, -offset) // translate to the origin
					* glm::rotate<float>(-90, 1, 0, 0); // turn to horizontal
				mvp = cameraManager.GetViewProj() * matWorld;

				shaderManager.SetUniform("MVP", mvp);
				shaderManager.SetTexture("texture_image", 0, coinTextureID);

				vertexBufferManager.Draw(GL_QUAD_STRIP, startOfCylinderShieldVertices, numberOfCylinderShieldVertices);
				vertexBufferManager.Draw(GL_TRIANGLE_FAN, startOfCylinderTopVertices, numberOfCylinderTopVertices);
				vertexBufferManager.Draw(GL_TRIANGLE_FAN, startOfCylinderBottomVertices, numberOfCylinderBottomVertices);
			}

			if (fields[i][j].hasDiamond())
			{
				const float diamondRotation = SDL_GetTicks() / 1000.0f * 360.0f / config::DIAMOND_ANIMATION_LENGTH;
				const float offset = config::FIELD_SIZE / 2.0f;
				
				matWorld = translateToCurrent
					* glm::translate<float>(offset, 0, offset) // translate to the middle
					* glm::rotate<float>(diamondRotation, 0, 1, 0); // for animation
				mvp = cameraManager.GetViewProj() * matWorld;

				shaderManager.SetUniform("MVP", mvp);
				shaderManager.SetTexture("texture_image", 0, diamondTextureID);

				vertexBufferManager.Draw(GL_TRIANGLE_FAN, startOfTopPyramidVertices, numberOfTopPyramidVertices);
				vertexBufferManager.Draw(GL_TRIANGLE_FAN, startOfBottomPyramidVertices, numberOfBottomPyramidVertices);
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

	shaderManager.SetUniform("isTheSunOrTheMoon", 1);

	//
	// draw the sun
	//

	const float orbitRadius = (config::MAP_SIZE * config::FIELD_SIZE * config::SUN_AND_MOON_ORBIT_RADIUS_MULTIPLIER) / 2.0f;
	const float sunRotation = SDL_GetTicks() / 1000.0f * 360.0f / config::SUN_AND_MOON_ANIMATION_LENGTH;
	const float middleOfTheMap = (config::MAP_SIZE * config::FIELD_SIZE) / 2.0f;

	matWorld = glm::translate<float>(middleOfTheMap, 0, middleOfTheMap) // translate to the middle of the map
		*glm::rotate<float>(sunRotation, 0, 0, 1) // rotate
		*glm::translate<float>(0, orbitRadius, 0) // translate up
		*glm::scale<float>(config::SUN_AND_MOON_SIZE, config::SUN_AND_MOON_SIZE, config::SUN_AND_MOON_SIZE); // set the size

	mvp = cameraManager.GetViewProj() * matWorld;
	shaderManager.SetUniform("MVP", mvp);

	vertexBufferManager.Draw(GL_QUAD_STRIP, startOfSphereVertices, numberOfSphereVertices);

	vertexBufferManager.Off();
	shaderManager.Off();

	//std::cout << "[onRender()] End" << std::endl;
}