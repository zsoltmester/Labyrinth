#include "Application.h"

#include <iostream>

#include "config.h"

void Application::drawWall(glm::mat4 matWorld)
{
	glm::mat4 mvp = cameraManager.GetViewProj() * matWorld;
	shaderManager.SetUniform("world", matWorld);
	shaderManager.SetUniform("worldInverseTranspose", glm::transpose(glm::inverse(matWorld)));
	shaderManager.SetUniform("MVP", mvp);
	shaderManager.SetTexture("textureImage", 0, wallTextureID);
	shaderManager.SetUniform("isASpecularMaterial", false);

	vertexBufferManager.Draw(GL_QUADS, startOfCuboidVertices, numberOfCuboidVertices);
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
	shaderManager.SetUniform("ambientLightColor", config::AMBIENT_LIGHT_COLOR);
	shaderManager.SetUniform("ambientLightStrength", config::AMBIENT_LIGHT_STRENGTH);
	shaderManager.SetUniform("sunDiffuseLightColor", config::SUN_DIFFUSE_LIGHT_COLOR);
	shaderManager.SetUniform("sunSpecularLightColor", config::SUN_SPECULAR_LIGHT_COLOR);
	shaderManager.SetUniform("moonDiffuseLightColor", config::MOON_DIFFUSE_LIGHT_COLOR);
	shaderManager.SetUniform("moonSpecularLightColor", config::MOON_SPECULAR_LIGHT_COLOR);
	shaderManager.SetUniform("specularLightStrength", config::SPECULAR_LIGHT_STRENGTH);
	shaderManager.SetUniform("specularLightSize", config::SPECULAR_LIGHT_SIZE);

	//
	// draw the sun an the moon
	//

	const float orbitRadius = (config::MAP_SIZE * config::FIELD_SIZE * config::SUN_AND_MOON_ORBIT_RADIUS_MULTIPLIER) / 2.0f;
	const float rotation = SDL_GetTicks() / 1000.0f * 360.0f / config::SUN_AND_MOON_ANIMATION_LENGTH;
	const float middleOfTheMap = (config::MAP_SIZE * config::FIELD_SIZE) / 2.0f;
	
	// sun

	shaderManager.SetUniform("isThisTheSunsVertex", true);

	matWorld = glm::translate<float>(middleOfTheMap, 0, middleOfTheMap) // translate to the middle of the map
		*glm::rotate<float>(rotation, 1, 0, 0) // rotate
		*glm::translate<float>(0, orbitRadius, 0) // translate up
		*glm::scale<float>(config::SUN_AND_MOON_SIZE, config::SUN_AND_MOON_SIZE, config::SUN_AND_MOON_SIZE); // set the size

	mvp = cameraManager.GetViewProj() * matWorld;
	shaderManager.SetUniform("MVP", mvp);

	vertexBufferManager.Draw(GL_QUAD_STRIP, startOfSphereVertices, numberOfSphereVertices);

	const glm::vec3 sunCurrentPosition = (matWorld * glm::vec4(0, 0, 0, 1)).xyz;
	const bool isTheSunUp = sunCurrentPosition.y > 0;
	shaderManager.SetUniform("sunPosition", sunCurrentPosition);
	shaderManager.SetUniform("isTheSunUp", isTheSunUp);
	if (isTheSunUp)
	{
		shaderManager.SetUniform("diffuseLightStrength",
			config::SUN_DIFFUSE_LIGHT_MAX_STRENGTH * (sunCurrentPosition.y / orbitRadius));
	}
	shaderManager.SetUniform("isThisTheSunsVertex", false);

	
	// moon

	shaderManager.SetUniform("isThisTheMoonsVertex", true);

	matWorld = glm::translate<float>(middleOfTheMap, 0, middleOfTheMap) // translate to the middle of the map
		*glm::rotate<float>(rotation, 1, 0, 0) // rotate
		*glm::translate<float>(0, -orbitRadius, 0) // translate down
		*glm::scale<float>(config::SUN_AND_MOON_SIZE, config::SUN_AND_MOON_SIZE, config::SUN_AND_MOON_SIZE); // set the size

	mvp = cameraManager.GetViewProj() * matWorld;
	shaderManager.SetUniform("MVP", mvp);

	vertexBufferManager.Draw(GL_QUAD_STRIP, startOfSphereVertices, numberOfSphereVertices);

	const glm::vec3 moonCurrentPosition = (matWorld * glm::vec4(0, 0, 0, 1)).xyz;
	const bool isTheMoonUp = moonCurrentPosition.y > 0;
	shaderManager.SetUniform("moonPosition", moonCurrentPosition);
	shaderManager.SetUniform("isTheMoonUp", isTheMoonUp);
	if (isTheMoonUp)
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
			glm::mat4 translateToCurrent 
				= glm::translate<float>(i * config::FIELD_SIZE, 0, j * config::FIELD_SIZE);

			//
			// the grass
			//

			mvp = cameraManager.GetViewProj() * translateToCurrent;

			shaderManager.SetUniform("world", translateToCurrent);
			shaderManager.SetUniform("worldInverseTranspose", glm::transpose(glm::inverse(translateToCurrent)));
			shaderManager.SetUniform("MVP", mvp);
			shaderManager.SetTexture("textureImage", 0, grassTextureID);
			shaderManager.SetUniform("isASpecularMaterial", false);
			vertexBufferManager.Draw(GL_QUADS, startOfQuadVertices, numberOfQuadVertices);

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

			if (!fields[i][j].hasCoin() && !fields[i][j].hasDiamond())
			{
				continue;
			}

			//
			// coin and diamond
			//

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

			mvp = cameraManager.GetViewProj() * matWorld;
			shaderManager.SetUniform("world", matWorld);
			shaderManager.SetUniform("worldInverseTranspose", glm::transpose(glm::inverse(matWorld)));
			shaderManager.SetUniform("MVP", mvp);
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

	vertexBufferManager.Off();
	shaderManager.Off();

	//std::cout << "[onRender()] End" << std::endl;
}