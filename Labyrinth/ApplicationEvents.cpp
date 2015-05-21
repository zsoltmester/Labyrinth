#include "Application.h"

#include "config.h"

bool canGoToDirection(Field field, Character::Direction characterDirection, Character::Direction moveDirection)
{
	switch (characterDirection)
	{
	case Character::X_PLUS:
	case Character::X_MINUS:
		if (moveDirection == Character::X_PLUS)
		{
			return !field.hasXPlusWall() && !field.isOnXPlusBorder();
		}
		else if (moveDirection == Character::X_MINUS)
		{
			return !field.hasXMinusWall() && !field.isOnXMinusBorder();
		}
		break;
	case Character::Z_PLUS:
	case Character::Z_MINUS:
		if (moveDirection == Character::Z_PLUS)
		{
			return !field.hasZPlusWall() && !field.isOnZPlusBorder();
		}
		else if (moveDirection == Character::Z_MINUS)
		{
			return !field.hasZMinusWall() && !field.isOnZMinusBorder();
		}
		break;
	}
	return false;
}

void Application::onKeyboardDown(SDL_KeyboardEvent& key)
{
	if (config::IS_DEBUG) {
		cameraManager.KeyboardDown(key);
		return;
	}

	if (hero->isAnimating())
	{
		return;
	}

	Field currentField = fields[hero->getCurrentPosition().x][hero->getCurrentPosition().z];

	switch (key.keysym.sym)
	{
	case SDLK_w:
		if (!canGoToDirection(currentField, hero->getCurrentDirection(), hero->getCurrentDirection()))
		{
			return;
		}
		hero->setMovingForward(true);
		hero->moveForward();
		break;
	case SDLK_s:
		Character::Direction backDirection;
		switch (hero->getCurrentDirection())
		{
		case Character::Z_PLUS:
			backDirection = Character::Z_MINUS;
			break;
		case Character::X_PLUS:
			backDirection = Character::X_MINUS;
			break;
		case Character::Z_MINUS:
			backDirection = Character::Z_PLUS;
			break;
		case Character::X_MINUS:
			backDirection = Character::X_PLUS;
			break;
		default:
			break;
		}
		if (!canGoToDirection(currentField, hero->getCurrentDirection(), backDirection))
		{
			return;
		}
		hero->setMovingBackward(true);
		hero->moveBackward();
		break;
	case SDLK_a:
		hero->setTurningLeft(true);
		hero->turnLeft();
		break;
	case SDLK_d:
		hero->setTurningRight(true);
		hero->turnRight();
		break;
	}
}

void Application::onKeyboardUp(SDL_KeyboardEvent& key)
{
	if (config::IS_DEBUG) {
		cameraManager.KeyboardUp(key);
	}
}

void Application::onMouseMove(SDL_MouseMotionEvent& mouse)
{
	if (config::IS_DEBUG) {
		cameraManager.MouseMove(mouse);
	}
}

void Application::onMouseDown(SDL_MouseButtonEvent& mouse)
{
	// nothing to do here
}

void Application::onMouseUp(SDL_MouseButtonEvent& mouse)
{
	// nothing to do here
}

void Application::onMouseWheel(SDL_MouseWheelEvent& wheel)
{
	// nothing to do here
}

void Application::onResize(const int width, const int height)
{
	glViewport(0, 0, width, height);
	cameraManager.Resize(width, height);
}