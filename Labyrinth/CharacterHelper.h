#pragma once

#include <glm/glm.hpp>

#include "Character.h"

// Helper methods for a character
class CharacterHelper
{
public:
	static glm::mat4 getRotationToDirectionMatrix(Hero* hero);
	static glm::mat4 getTranslateToHeroPositionMatrix(Hero* hero);
	static glm::mat4 getTranslateToTheMiddleOfTheFieldMatrix(Hero* hero);
	static glm::mat4 getMovingTranslateMatrix(Hero* hero);
	static glm::mat4 getTurningRotationMatrix(Hero* hero);
};
