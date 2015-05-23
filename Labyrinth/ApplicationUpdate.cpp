#include "Application.h"

#include "config.h"
#include "CharacterHelper.h"
 
void Application::onUpdate()
{
	//
	// Debug
	//

	if (config::IS_DEBUG) 
	{
		static Uint32 last_time = SDL_GetTicks();
		const float delta_time = (SDL_GetTicks() - last_time) / 1000.0f;
		cameraManager.Update(delta_time);
		last_time = SDL_GetTicks();
		return;
	}

	Field* currentField = &fields[hero->getCurrentPosition().x][hero->getCurrentPosition().z];
	
	//
	// Check if hero collected a coin or a diamond
	//

	if (currentField->hasCoin())
	{
		currentField->setHasCoin(false);
		++collectedCoins;
		std::cout << "[onUpdate()] Coin collected! Number of coins: " << collectedCoins << std::endl;
	}
	if (currentField->hasDiamond())
	{
		currentField->setHasDiamond(false);
		++collectedDiamonds;
		std::cout << "[onUpdate()] Diamond collected! Number of diamonds: " << collectedDiamonds << std::endl;
		if (collectedDiamonds == config::NUMBER_OF_DIAMONDS) 
		{
			isWin = true;
		}
	}

	//
	// In case of win
	//

	if (isWin)
	{
		float jumpSize = (collectedCoins / (float)config::NUMBER_OF_COINS) * config::JUMP_MULTIPLIER;

		glm::vec4 eye = glm::vec4(
			config::FIELD_SIZE * 3,
			jumpSize * 1.5f,
			config::FIELD_SIZE * 3,
			1
		);

		glm::vec4 at = glm::vec4(0, jumpSize / 2, 0, 1);

		const glm::mat4 translateToHeroPosition = CharacterHelper::getTranslateToHeroPositionMatrix(hero);
		const glm::mat4 translateToTheMiddleOfTheField = CharacterHelper::getTranslateToTheMiddleOfTheFieldMatrix(hero);
		float cameraRotation = SDL_GetTicks() / 1000.0f * 360.0f / config::CAMERA_ROTATION_ANIMATION_LENGTH;
		const glm::mat4 rotation = glm::rotate<float>(cameraRotation, 0, 1, 0);

		eye = translateToTheMiddleOfTheField
			* translateToHeroPosition
			* rotation
			* eye;

		at = translateToTheMiddleOfTheField
			* translateToHeroPosition
			* rotation
			* at;

		cameraManager.SetView(eye.xyz, at.xyz, glm::vec3(0, 1, 0));

		return;
	}

	if (isGameOver)
	{
		float directionBasedOffsetX = 0;
		float directionBasedOffsetZ = 0;
		switch (hero->getCurrentDirection())
		{
		case Character::X_PLUS:
			directionBasedOffsetX = -config::FIELD_SIZE;
			break;
		case Character::X_MINUS:
			directionBasedOffsetX = config::FIELD_SIZE;
			break;
		case Character::Z_PLUS:
			directionBasedOffsetZ = -config::FIELD_SIZE;
			break;
		case Character::Z_MINUS:
			directionBasedOffsetZ = config::FIELD_SIZE;
			break;
		default:
			break;
		}

		glm::vec4 eye = glm::vec4(
			-directionBasedOffsetX,
			config::FIELD_SIZE / 2.0f,
			-directionBasedOffsetZ,
			1
		);

		glm::vec4 at = glm::vec4(
			0,
			config::FIELD_SIZE / 2.0f,
			0,
			1
		);

		const glm::mat4 translateToHeroPosition = CharacterHelper::getTranslateToHeroPositionMatrix(hero);
		const glm::mat4 translateToTheMiddleOfTheField = CharacterHelper::getTranslateToTheMiddleOfTheFieldMatrix(hero);
		
		glm::mat4 gameOverTranslate;
		static float animationSize;
		if (gameOverLastRenderingTime > 0)
		{
			animationSize = (config::FIELD_SIZE / 4.0f) * (xGameOverFunctionParameter / config::HERO_ROTATION_LENGTH_AT_GAME_OVER);
		}

		switch (hero->getCurrentDirection())
		{
		case Character::X_PLUS:
			gameOverTranslate = glm::translate<float>(-animationSize, 0, 0);
			break;
		case Character::X_MINUS:
			gameOverTranslate = glm::translate<float>(animationSize, 0, 0);
			break;
		case Character::Z_PLUS:
			gameOverTranslate = glm::translate<float>(0, 0, -animationSize);
			break;
		case Character::Z_MINUS:
			gameOverTranslate = glm::translate<float>(0, 0, animationSize);
			break;
		default:
			break;
		}

		eye = gameOverTranslate
			* translateToTheMiddleOfTheField
			* translateToHeroPosition
			* eye;

		at = translateToTheMiddleOfTheField
			* translateToHeroPosition
			* at;

		cameraManager.SetView(eye.xyz, at.xyz, glm::vec3(0, 1, 0));

		return;
	}

	//
	// Check if current position is a portal
	//

	if (isPortalActive && currentField->hasPortal()) 
	{
		for (short i = 0; i < config::MAP_SIZE && isPortalActive; ++i)
		{
			for (short j = 0; j < config::MAP_SIZE && isPortalActive; ++j)
			{
				if (fields[i][j].hasPortal() && !(hero->getCurrentPosition().x == i && hero->getCurrentPosition().z == j))
				{
					hero->teleport(Character::Position(i, j));
					lastPortalPosition = Character::Position(i,j);
					isPortalActive = false;
				}
			}
		}
	}
	else if (!isPortalActive 
		&& (lastPortalPosition.x != hero->getCurrentPosition().x 
		|| lastPortalPosition.z != hero->getCurrentPosition().z))
	{
		isPortalActive = true;
	}

	//
	// Set the characters animation time
	//

	if (hero->isAnimating())
	{
		static Uint32 last_time;
		if (hero->getAnimationTime() > 0)
		{
			hero->setAnimationTime(hero->getAnimationTime() + SDL_GetTicks() - last_time);
		}
		else
		{
			hero->setAnimationTime(1); // TODO It's a hack...
		}
		if (hero->getAnimationTime() > config::MOVEMENT_TIME_IN_MS)
		{
			hero->turnOffAnimation();
		}
		last_time = SDL_GetTicks();
	}

	//
	// Top view
	//

	if (isTopView)
	{
		const int rawHalfMapSize = config::MAP_SIZE / 2;
		const float halfMapSize = rawHalfMapSize * config::FIELD_SIZE;
		const glm::vec3 at = glm::vec3(
			halfMapSize + config::FIELD_SIZE / 2 + 0.00001f,
			0,
			halfMapSize + config::FIELD_SIZE / 2);
		const glm::vec3 eye = glm::vec3(
			halfMapSize + config::FIELD_SIZE / 2,
			1.3f * config::MAP_SIZE * config::FIELD_SIZE,
			halfMapSize + config::FIELD_SIZE / 2);
		cameraManager.SetView(eye, at, glm::vec3(0, 1, 0));
		return;
	}

	//
	// Set the camera
	//

	float directionBasedOffsetX = 0;
	float directionBasedOffsetZ = 0;
	switch (hero->getCurrentDirection())
	{
	case Character::X_PLUS:
		directionBasedOffsetX = -config::FIELD_SIZE;
		break;
	case Character::X_MINUS:
		directionBasedOffsetX = config::FIELD_SIZE;
		break;
	case Character::Z_PLUS:
		directionBasedOffsetZ = -config::FIELD_SIZE;
		break;
	case Character::Z_MINUS:
		directionBasedOffsetZ = config::FIELD_SIZE;
		break;
	default:
		break;
	}

	glm::vec4 eye = glm::vec4(
		directionBasedOffsetX,
		config::WALL_HEIGHT * 1.5f,
		directionBasedOffsetZ,
		1
	);

	glm::vec4 at = glm::vec4(
		-directionBasedOffsetX,
		0,
		-directionBasedOffsetZ,
		1
	);

	const glm::mat4 translateToHeroPosition = CharacterHelper::getTranslateToHeroPositionMatrix(hero);
	const glm::mat4 translateToTheMiddleOfTheField = CharacterHelper::getTranslateToTheMiddleOfTheFieldMatrix(hero);
	glm::mat4 movingTranslate = CharacterHelper::getMovingTranslateMatrix(hero);
	glm::mat4 turningRotation = CharacterHelper::getTurningRotationMatrix(hero);

	eye = movingTranslate
		* translateToTheMiddleOfTheField
		* translateToHeroPosition
		* turningRotation
		* eye;

	at = movingTranslate
		* translateToTheMiddleOfTheField
		* translateToHeroPosition
		* turningRotation
		* at;

	cameraManager.SetView(eye.xyz, at.xyz, glm::vec3(0, 1, 0));
}