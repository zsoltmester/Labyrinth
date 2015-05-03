#include "Field.h"

const bool Field::hasLeftWall() const
{
	return _hasLeftWall;
}

const bool Field::hasRightWall() const
{
	return _hasRightWall;
}

const bool Field::hasUpperWall() const
{
	return _hasUpperWall;
}

const bool Field::hasLowerWall() const
{
	return _hasLowerWall;
}

void Field::setHasLeftWall(const bool hasLeftWall)
{
	_hasLeftWall = hasLeftWall;
}

void Field::setHasRightWall(const bool hasRightWall)
{
	_hasRightWall = hasRightWall;
}

void Field::setHasUpperWall(const bool hasUpperWall)
{
	_hasUpperWall = hasUpperWall;
}

void Field::setHasLowerWall(const bool hasLowerWall)
{
	_hasLowerWall = hasLowerWall;
}

const bool Field::isOnLeftBorder() const
{
	return _isOnLeftBorder;
}

const bool Field::isOnRightBorder() const
{
	return _isOnRightBorder;
}

const bool Field::isOnUpperBorder() const
{
	return _isOnUpperBorder;
}

const bool Field::isOnLowerBorder() const
{
	return _isOnLowerBorder;
}

void Field::setIsOnLeftBorder(const bool isOnLeftBorder)
{
	_isOnLeftBorder = isOnLeftBorder;
}

void Field::setIsOnRightBorder(const bool isOnRightBorder)
{
	_isOnRightBorder = isOnRightBorder;
}

void Field::setIsOnUpperBorder(const bool isOnUpperBorder)
{
	_isOnUpperBorder = isOnUpperBorder;
}

void Field::setIsOnLowerBorder(const bool isOnLowerBorder)
{
	_isOnLowerBorder = isOnLowerBorder;
}

const bool Field::hasCoin() const
{
	return _hasCoin;
}

const bool Field::hasDiamond() const
{
	return _hasDiamond;
}

void Field::setHasCoin(const bool hasCoin)
{
	_hasCoin = hasCoin;
}

void Field::setHasDiamond(const bool hasDiamond)
{
	_hasDiamond = hasDiamond;
}


const bool Field::hasPortal(const PortalType portal) const
{
	return _portal == portal;
}

void Field::setHasPortal(const PortalType portal)
{
	_portal = portal;
}