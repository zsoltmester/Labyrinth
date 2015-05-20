#include "Character.h"

// ***
// Character class
// ***

Character::Character(Character::Position position, Direction direction) 
	: _position(position), _direction(direction)
{
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
	if (_isMoving)
	{
		return;
	}

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
	if (_isMoving)
	{
		return;
	}

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
	if (_isMoving)
	{
		return;
	}

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

void Character::turnRight()
{
	if (_isMoving)
	{
		return;
	}

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

bool Character::isMoving() const
{
	return _isMoving;
}

void Character::setMoving(bool isMoving)
{
	_isMoving = isMoving;
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