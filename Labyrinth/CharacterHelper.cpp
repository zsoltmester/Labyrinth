#include "CharacterHelper.h"
#include "config.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>

glm::mat4 CharacterHelper::getRotationToDirectionMatrix(Hero* hero)
{
	return glm::rotate<float>(hero->getCurrentDirection() * 90, 0, 1, 0);
}

glm::mat4 CharacterHelper::getTranslateToHeroPositionMatrix(Hero* hero)
{
	return glm::translate<float>(
		hero->getCurrentPosition().x * config::FIELD_SIZE, 0, hero->getCurrentPosition().z * config::FIELD_SIZE);
}

glm::mat4 CharacterHelper::getTranslateToTheMiddleOfTheFieldMatrix(Hero* hero)
{
	const float offset = config::FIELD_SIZE / 2.0f;
	return glm::translate<float>(offset, 0, offset);
}

glm::mat4 CharacterHelper::getMovingTranslateMatrix(Hero* hero)
{
	glm::mat4 movingTranslate = glm::mat4(1);

	if (!hero->isMovingForward() && !hero->isMovingBackward())
	{
		return movingTranslate;
	}

	const float currentPercent = hero->getAnimationTime() / (float)config::MOVEMENT_TIME_IN_MS;
	const float currentDistance = currentPercent * config::FIELD_SIZE - config::FIELD_SIZE;

	if (hero->isMovingForward())
	{
		switch (hero->getCurrentDirection())
		{
		case Character::X_PLUS:
			movingTranslate = glm::translate<float>(currentDistance, 0, 0);
			break;
		case Character::X_MINUS:
			movingTranslate = glm::translate<float>(-currentDistance, 0, 0);
			break;
		case Character::Z_PLUS:
			movingTranslate = glm::translate<float>(0, 0, currentDistance);
			break;
		case Character::Z_MINUS:
			movingTranslate = glm::translate<float>(0, 0, -currentDistance);
			break;
		default:
			break;
		}
	}

	if (hero->isMovingBackward())
	{
		switch (hero->getCurrentDirection())
		{
		case Character::X_PLUS:
			movingTranslate = glm::translate<float>(-currentDistance, 0, 0);
			break;
		case Character::X_MINUS:
			movingTranslate = glm::translate<float>(currentDistance, 0, 0);
			break;
		case Character::Z_PLUS:
			movingTranslate = glm::translate<float>(0, 0, -currentDistance);
			break;
		case Character::Z_MINUS:
			movingTranslate = glm::translate<float>(0, 0, currentDistance);
			break;
		default:
			break;
		}
	}

	return movingTranslate;
}

glm::mat4 CharacterHelper::getTurningRotationMatrix(Hero* hero)
{
	glm::mat4 turningRotation = glm::mat4(1);

	if (!hero->isTurningLeft() && !hero->isTurningRight())
	{
		return turningRotation;
	}

	const float currentPercent = hero->getAnimationTime() / (float)config::MOVEMENT_TIME_IN_MS;

	if (hero->isTurningLeft())
	{
		turningRotation = glm::rotate<float>(-90 + 90 * currentPercent, 0, 1, 0);
	}

	if (hero->isTurningRight())
	{
		turningRotation = glm::rotate<float>(90 - 90 * currentPercent, 0, 1, 0);
	}

	return turningRotation;
}