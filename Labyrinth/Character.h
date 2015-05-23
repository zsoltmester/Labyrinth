#pragma once

// Represents a character, like the hero or the monsters
class Character
{

public:

	struct Position
	{
		int x;
		int z;

		Position(int x, int z)
		{
			this->x = x;
			this->z = z;
		}
	};

	const enum Direction
	{
		Z_PLUS, X_PLUS,
		Z_MINUS, X_MINUS
	};

	Character(Position, Direction);
	~Character(void);

	virtual int getType() = 0;

	// Returns the character's current position
	Position getCurrentPosition() const;

	// Returns the character's current direction
	Direction getCurrentDirection() const;

	// Moves the character forward
	void moveForward();

	// Moves the character backward
	void moveBackward();

	// Turns the character left
	void turnLeft();

	// Turns the character right
	void turnRight();

	// Return true, if the character is moving forward, otherwise false
	bool isMovingForward() const;

	// Set, if the character is moving forward or not
	void setMovingForward(bool);

	// Return true, if the character is moving backward, otherwise false
	bool isMovingBackward() const;

	// Set, if the character is moving backward or not
	void setMovingBackward(bool);

	// Return true, if the character is turning left, otherwise false
	bool isTurningLeft() const;

	// Set, if the character is turning left or not
	void setTurningLeft(bool);

	// Return true, if the character is turning right, otherwise false
	bool isTurningRight() const;

	// Set, if the character is turning right or not
	void setTurningRight(bool);

	// Returns the animation current length
	int getAnimationTime() const;

	// Sets the animation current length
	void setAnimationTime(int);

	// Returns if the character is animation currently
	bool isAnimating() const;

	// Turn off the animation state
	void turnOffAnimation();

	// Teleport to a position
	void teleport(Position);

private:

	Position _position;
	Direction _direction;
	bool _isMovingForward;
	bool _isMovingBackward;
	bool _isTurningLeft;
	bool _isTurningRight;
	int _animationTime;
};


class Hero : public Character
{

public:

	Hero(Position, Direction);

	static const int TYPE_HERO = 0;
	int getType();
};


class Monster : public Character
{

public:

	Monster(Position, Direction);

	static const int TYPE_MONSTER = 1;
	int getType();
};