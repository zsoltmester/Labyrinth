#include "Character.h"

// ***
// Character class
// ***

Character::Character(Character::Position position, Direction direction) 
	: _position(position), _direction(direction)
{
	_isMovingForward = false;
	_isMovingBackward = false;
	_isTurningLeft = false;
	_isTurningRight = false;
	_animationTime = 0;
}

Character::~Character()
{
}

Character::Position Character::getCurrentPosition() const
{
	return _position;
}

Character::Direction Character::getCurrentDirection() const
{
	return _direction;
}

void Character::moveForward()
{
	switch (_direction)
	{
	case X_PLUS:
		++_position.x;
		break;
	case X_MINUS:
		--_position.x;
		break;
	case Z_PLUS:
		++_position.z;
		break;
	case Z_MINUS:
		--_position.z;
		break;
	}
}

void Character::moveBackward()
{
	switch (_direction)
	{
	case X_PLUS:
		--_position.x;
		break;
	case X_MINUS:
		++_position.x;
		break;
	case Z_PLUS:
		--_position.z;
		break;
	case Z_MINUS:
		++_position.z;
		break;
	}
}

void Character::turnLeft()
{
	switch (_direction)
	{
	case X_PLUS:
		_direction = Z_MINUS;
		break;
	case Z_MINUS:
		_direction = X_MINUS;
		break;
	case X_MINUS:
		_direction = Z_PLUS;
		break;
	case Z_PLUS:
		_direction = X_PLUS;
		break;
	}
}

void Character::turnRight()
{
	switch (_direction)
	{
	case X_PLUS:
		_direction = Z_PLUS;
		break;
	case Z_PLUS:
		_direction = X_MINUS;
		break;
	case X_MINUS:
		_direction = Z_MINUS;
		break;
	case Z_MINUS:
		_direction = X_PLUS;
		break;
	}
}

bool Character::isMovingForward() const
{
	return _isMovingForward;
}
void Character::setMovingForward(bool isMovingForward)
{
	_isMovingForward = isMovingForward;
}
bool Character::isMovingBackward() const
{
	return _isMovingBackward;
}
void Character::setMovingBackward(bool isMovingBackward)
{
	_isMovingBackward = isMovingBackward;
}
bool Character::isTurningLeft() const
{
	return _isTurningLeft;
}
void Character::setTurningLeft(bool isTurningLeft)
{
	_isTurningLeft = isTurningLeft;
}
bool Character::isTurningRight() const
{
	return _isTurningRight;
}
void Character::setTurningRight(bool isTurningRight)
{
	_isTurningRight = isTurningRight;
}

// Returns the animation current length
int Character::getAnimationTime() const
{
	return _animationTime;
}

// Sets the animation current length
void Character::setAnimationTime(int animationTime)
{
	_animationTime = animationTime;
}


bool Character::isAnimating() const
{
	return isMovingForward() || isMovingBackward() || isTurningLeft() || isTurningRight();
}

void Character::turnOffAnimation()
{
	setMovingForward(false);
	setMovingBackward(false);
	setTurningLeft(false);
	setTurningRight(false);
	_animationTime = 0;
}

// ***
// Hero class
// ***

Hero::Hero(Position position, Direction direction) : Character(position, direction)
{
}

int Hero::getType()
{
	return TYPE_HERO;
}

// ***
// Monster class
// ***

Monster::Monster(Position position, Direction direction) : Character(position, direction)
{
}

int Monster::getType()
{
	return TYPE_MONSTER;
}