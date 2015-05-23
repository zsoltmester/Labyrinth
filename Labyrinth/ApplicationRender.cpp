#include "Application.h"

#include <iostream>

#include "config.h"
#include "CharacterHelper.h"

void Application::drawWall(glm::mat4 matWorld)
{
	shaderManager.SetUniform("world", matWorld);
	shaderManager.SetUniform("worldInverseTranspose", glm::transpose(glm::inverse(matWorld)));
	shaderManager.SetUniform("MVP", cameraManager.GetViewProj() * matWorld);
	shaderManager.SetTexture("textureImage", 0, wallTextureID);
	shaderManager.SetUniform("isASpecularMaterial", false);
	vertexBufferManager.Draw(GL_QUADS, startOfCuboidVertices, numberOfCuboidVertices);
}

const glm::vec3 Application::drawOrb(const float orbitRadius)
{
	const float rotation = SDL_GetTicks() / 1000.0f * 360.0f / config::SUN_AND_MOON_ANIMATION_LENGTH;
	const float middleOfTheMap = (config::MAP_SIZE * config::FIELD_SIZE) / 2.0f;

	const glm::mat4 matWorld = glm::translate<float>(middleOfTheMap, 0, middleOfTheMap) // translate to the middle of the map
		*glm::rotate<float>(rotation, 1, 0, 0) // rotate
		*glm::translate<float>(0, orbitRadius, 0) // translate up or down
		*glm::scale<float>(config::SUN_AND_MOON_SIZE, config::SUN_AND_MOON_SIZE, config::SUN_AND_MOON_SIZE); // set the size

	shaderManager.SetUniform("MVP", cameraManager.GetViewProj() * matWorld);
	vertexBufferManager.Draw(GL_QUAD_STRIP, startOfSphereVertices, numberOfSphereVertices);
	return (matWorld * glm::vec4(0, 0, 0, 1)).xyz;
}

void Application::onRender()
{
	//std::cout << "[onRender()] Start" << std::endl;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shaderManager.On();
	vertexBufferManager.On();

	glm::mat4 matWorld;
	glm::mat4 mvp;

	shaderManager.SetUniform("eyePosition", cameraManager.GetEye());

	//
	// draw the sun and the moon
	//

	const float orbitRadius = (config::MAP_SIZE * config::FIELD_SIZE * config::SUN_AND_MOON_ORBIT_RADIUS_MULTIPLIER) / 2.0f;
	
	// sun
	shaderManager.SetUniform("isThisTheSunsVertex", true);
	const glm::vec3 sunCurrentPosition = drawOrb(orbitRadius);
	shaderManager.SetUniform("sunPosition", sunCurrentPosition);
	if (sunCurrentPosition.y > 0)
	{
		shaderManager.SetUniform("diffuseLightStrength",
			config::SUN_DIFFUSE_LIGHT_MAX_STRENGTH * (sunCurrentPosition.y / orbitRadius));
	}
	shaderManager.SetUniform("isThisTheSunsVertex", false);

	
	// moon
	shaderManager.SetUniform("isThisTheMoonsVertex", true);
	const glm::vec3 moonCurrentPosition = drawOrb(-orbitRadius);
	shaderManager.SetUniform("moonPosition", moonCurrentPosition);
	if (moonCurrentPosition.y > 0)
	{
		shaderManager.SetUniform("diffuseLightStrength", 
			config::MOON_DIFFUSE_LIGHT_MAX_STRENGTH * (moonCurrentPosition.y / orbitRadius));
	}
	shaderManager.SetUniform("isThisTheMoonsVertex", false);
	
	//
	// draw the fields
	//

	for (short i = 0; i < config::MAP_SIZE; ++i) 
	{
		for (short j = 0; j < config::MAP_SIZE; ++j) 
		{
			const glm::mat4 translateToCurrent = 
				glm::translate<float>(i * config::FIELD_SIZE, 0, j * config::FIELD_SIZE);

			// check if it's a portal
			if (fields[i][j].hasPortal())
			{
				shaderManager.SetUniform("isThisAFieldWithAPortal", true);
				const float middleOfTheField = config::FIELD_SIZE / 2.0f;
				shaderManager.SetUniform("portalLightSourcePosition", 
					(translateToCurrent * glm::vec4(middleOfTheField, config::WALL_HEIGHT, middleOfTheField, 1)).xyz);
			} 
			else
			{
				shaderManager.SetUniform("isThisAFieldWithAPortal", false);
			}

			//
			// the grass
			//

			shaderManager.SetUniform("world", translateToCurrent);
			shaderManager.SetUniform("worldInverseTranspose", glm::transpose(glm::inverse(translateToCurrent)));
			shaderManager.SetUniform("MVP", cameraManager.GetViewProj() * translateToCurrent);
			shaderManager.SetTexture("textureImage", 0, grassTextureID);
			shaderManager.SetUniform("isASpecularMaterial", false);
			vertexBufferManager.Draw(GL_QUADS, startOfQuadVertices, numberOfQuadVertices);

			//
			// the walls
			//

			if (fields[i][j].hasZMinusWall())
			{
				drawWall(translateToCurrent);
			}

			if (fields[i][j].hasZPlusWall())
			{
				matWorld = translateToCurrent 
					* glm::translate<float>(0, 0, config::FIELD_SIZE - config::WALL_THICKNESS);
				drawWall(matWorld);
			}

			if (fields[i][j].hasXPlusWall())
			{
				matWorld = translateToCurrent
					* glm::translate<float>(config::FIELD_SIZE, 0, 0)
					* glm::rotate<float>(-90, 0, 1, 0);
				drawWall(matWorld);
			}

			if (fields[i][j].hasXMinusWall())
			{
				matWorld = translateToCurrent
					* glm::translate<float>(config::WALL_THICKNESS, 0, 0)
					* glm::rotate<float>(-90, 0, 1, 0);
				drawWall(matWorld);
			}

			//
			// coin and diamond
			//

			if (!fields[i][j].hasCoin() && !fields[i][j].hasDiamond())
			{
				continue;
			}

			const float offset = config::FIELD_SIZE / 2.0f;
			matWorld = translateToCurrent
				* glm::translate<float>(offset, 0, offset); // translate to the middle of the field

			// rotate
			if (fields[i][j].hasCoin())
			{
				const float coinRotation = SDL_GetTicks() / 1000.0f * 360.0f / config::COIN_ANIMATION_LENGTH;
				matWorld *= glm::rotate<float>(coinRotation, 0, 1, 0); // for animation
			}
			else if (fields[i][j].hasDiamond())
			{
				const float diamondRotation = SDL_GetTicks() / 1000.0f * 360.0f / config::DIAMOND_ANIMATION_LENGTH;
				matWorld *= glm::rotate<float>(diamondRotation, 0, 1, 0); // for animation
			}

			shaderManager.SetUniform("world", matWorld);
			shaderManager.SetUniform("worldInverseTranspose", glm::transpose(glm::inverse(matWorld)));
			shaderManager.SetUniform("MVP", cameraManager.GetViewProj() * matWorld);
			shaderManager.SetUniform("isASpecularMaterial", true);

			// set the texture and draw the geometry
			if (fields[i][j].hasCoin())
			{
				shaderManager.SetTexture("textureImage", 0, coinTextureID);
				vertexBufferManager.Draw(GL_QUAD_STRIP, startOfCylinderShieldVertices, numberOfCylinderShieldVertices);
				vertexBufferManager.Draw(GL_TRIANGLE_FAN, startOfCylinderBottomVertices, numberOfCylinderBottomVertices);
				vertexBufferManager.Draw(GL_TRIANGLE_FAN, startOfCylinderTopVertices, numberOfCylinderTopVertices);
			}
			else if (fields[i][j].hasDiamond())
			{
				shaderManager.SetTexture("textureImage", 0, diamondTextureID);
				vertexBufferManager.Draw(GL_TRIANGLE_FAN, startOfBottomPyramidVertices, numberOfBottomPyramidVertices);
				vertexBufferManager.Draw(GL_TRIANGLE_FAN, startOfTopPyramidVertices, numberOfTopPyramidVertices);
			}
		}
	}

	//
	// draw the hero
	//

	if (!isWin && !isGameOver)
	{
		const glm::mat4 rotateToDirection = CharacterHelper::getRotationToDirectionMatrix(hero);

		const glm::mat4 scaleDown = glm::scale<float>(
			config::FIELD_SIZE / 3.5f, config::FIELD_SIZE / 3.5f, config::FIELD_SIZE / 3.5f);

		const glm::mat4 translateToHeroPosition = CharacterHelper::getTranslateToHeroPositionMatrix(hero);
		const glm::mat4 translateToTheMiddleOfTheField = CharacterHelper::getTranslateToTheMiddleOfTheFieldMatrix(hero);
		const glm::mat4 translateToUp = glm::translate<float>(0, config::FIELD_SIZE / 2.0f, 0);

		glm::mat4 movingTranslate = CharacterHelper::getMovingTranslateMatrix(hero);
		glm::mat4 turningRotation = CharacterHelper::getTurningRotationMatrix(hero);

		matWorld = movingTranslate
			* translateToUp
			* translateToTheMiddleOfTheField
			* translateToHeroPosition
			* scaleDown
			* turningRotation
			* rotateToDirection;
	}
	else if (isWin)
	{
		const glm::mat4 rotateToDirection = CharacterHelper::getRotationToDirectionMatrix(hero);

		const glm::mat4 scaleDown = glm::scale<float>(
			config::FIELD_SIZE / 3.5f, config::FIELD_SIZE / 3.5f, config::FIELD_SIZE / 3.5f);

		const glm::mat4 translateToHeroPosition = CharacterHelper::getTranslateToHeroPositionMatrix(hero);
		const glm::mat4 translateToTheMiddleOfTheField = CharacterHelper::getTranslateToTheMiddleOfTheFieldMatrix(hero);
		const glm::mat4 translateToUp = glm::translate<float>(0, config::FIELD_SIZE / 2.0f, 0);

		// *** jump function:
		// 0 <= x <= JUMP_LENGTH (-> from 0 to jumpSize): (x / JUMP_LENGTH) * jumpSize
		// JUMP_LENGTH < x <= 2*JUMP_LENGTH (-> from jumpSize to 0): (1 - ((x - JUMP_LENGTH) / JUMP_LENGTH)) * jumpSize

		glm::mat4 jumpTranslate = glm::mat4(0);
		float jumpSize = (collectedCoins / (float)config::NUMBER_OF_COINS) * config::JUMP_MULTIPLIER;
		if (winLastRenderingTime != 0)
		{
			xWinFunctionParameter += SDL_GetTicks() - winLastRenderingTime;

			float y;
			if (xWinFunctionParameter <= config::JUMP_LENGTH)
			{
				y = (xWinFunctionParameter / config::JUMP_LENGTH) * jumpSize;
			}
			else if (xWinFunctionParameter <= 2 * config::JUMP_LENGTH)
			{
				y = (1 - ((xWinFunctionParameter - config::JUMP_LENGTH) / config::JUMP_LENGTH)) * jumpSize;
			}
			else
			{
				y = 0;
				xWinFunctionParameter = 0;
			}

			jumpTranslate = glm::translate<float>(0, y, 0);
			winLastRenderingTime = SDL_GetTicks();
		}
		else
		{
			winLastRenderingTime = SDL_GetTicks();
		}
		

		matWorld = jumpTranslate
			* translateToUp
			* translateToTheMiddleOfTheField
			* translateToHeroPosition
			* scaleDown
			* rotateToDirection;
	} 
	else
	{
		// game over

		const glm::mat4 rotateToDirection = CharacterHelper::getRotationToDirectionMatrix(hero);

		const glm::mat4 scaleDown = glm::scale<float>(
			config::FIELD_SIZE / 3.5f, config::FIELD_SIZE / 3.5f, config::FIELD_SIZE / 3.5f);

		const glm::mat4 translateToHeroPosition = CharacterHelper::getTranslateToHeroPositionMatrix(hero);
		const glm::mat4 translateToTheMiddleOfTheField = CharacterHelper::getTranslateToTheMiddleOfTheFieldMatrix(hero);
		const glm::mat4 translateToUp = glm::translate<float>(0, config::FIELD_SIZE / 2.0f, 0);

		glm::mat4 gameOverRotation = glm::mat4(1);
		if (gameOverLastRenderingTime > 0)
		{
			xGameOverFunctionParameter += SDL_GetTicks() - gameOverLastRenderingTime;

			float y;
			if (xGameOverFunctionParameter <= config::HERO_ROTATION_LENGTH_AT_GAME_OVER)
			{
				y = (xGameOverFunctionParameter / config::HERO_ROTATION_LENGTH_AT_GAME_OVER) * 45;
				gameOverRotation = glm::rotate<float>(y, 1, 0, 0);
				gameOverLastRenderingTime = SDL_GetTicks();
			}
			else
			{
				y = 45;
				gameOverLastRenderingTime = -1;
				gameOverRotation = glm::rotate<float>(y, 1, 0, 0);
			}

		}
		else if (gameOverLastRenderingTime == 0)
		{
			gameOverLastRenderingTime = SDL_GetTicks();
		}
		else
		{
			gameOverRotation = glm::rotate<float>(45, 1, 0, 0);
		}

		matWorld = translateToUp
			* translateToTheMiddleOfTheField
			* translateToHeroPosition
			* scaleDown
			* rotateToDirection
			* gameOverRotation;

	}

	shaderManager.SetUniform("world", matWorld);
	shaderManager.SetUniform("worldInverseTranspose", glm::transpose(glm::inverse(matWorld)));
	shaderManager.SetUniform("MVP", cameraManager.GetViewProj() * matWorld);
	shaderManager.SetTexture("textureImage", 0, suzanneTextureID);
	shaderManager.SetUniform("isASpecularMaterial", true);
	heroMesh->draw();

	//
	// turn off the managers
	//

	vertexBufferManager.Off();
	shaderManager.Off();

	//std::cout << "[onRender()] End" << std::endl;
}