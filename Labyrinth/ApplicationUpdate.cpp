#include "Application.h"

#include "config.h"
 
void Application::onUpdate()
{
	//
	// Set the camera
	//

	if (config::IS_DEBUG) 
	{
		static Uint32 last_time = SDL_GetTicks();
		const float delta_time = (SDL_GetTicks() - last_time) / 1000.0f;
		cameraManager.Update(delta_time);
		last_time = SDL_GetTicks();
		return;
	}

	const float middleOfTheFieldOffset = config::FIELD_SIZE / 2.0f;
	float directionBasedOffsetX = 0;
	float directionBasedOffsetZ = 0;

	switch (hero->getCurrentDirection())
	{
	case Character::X_PLUS:
		directionBasedOffsetX = -1;
		break;
	case Character::X_MINUS:
		directionBasedOffsetX = 1;
		break;
	case Character::Z_PLUS:
		directionBasedOffsetZ = -1;
		break;
	case Character::Z_MINUS:
		directionBasedOffsetZ = 1;
		break;
	default:
		break;
	}

	if (hero->isAnimating())
	{
		// TODO ...
	}

	glm::vec3 eye = glm::vec3(
		hero->getCurrentPosition().x + middleOfTheFieldOffset + directionBasedOffsetX,
		config::WALL_HEIGHT * 1.5f, 
		hero->getCurrentPosition().z + middleOfTheFieldOffset + directionBasedOffsetZ
	);

	glm::vec3 at = glm::vec3(
		hero->getCurrentPosition().x + middleOfTheFieldOffset - directionBasedOffsetX,
		0,
		hero->getCurrentPosition().z + middleOfTheFieldOffset - directionBasedOffsetZ
	);

	cameraManager.SetView(eye, at, glm::vec3(0, 1, 0));

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
}