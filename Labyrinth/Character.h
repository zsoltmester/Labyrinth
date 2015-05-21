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

	// Return true, if the character is on move, otherwise false
	bool isMoving() const;

	// Set, if the character is on move or not
	void setMoving(bool);

private:
	
	Position _position;
	Direction _direction;
	bool _isMoving;
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