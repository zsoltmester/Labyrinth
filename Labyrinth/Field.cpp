#include "Field.h"

const bool Field::hasZMinusWall() const
{
	return _hasZMinusWall;
}

const bool Field::hasZPlusWall() const
{
	return _hasZPlusWall;
}

const bool Field::hasXPlusWall() const
{
	return _hasXPlusWall;
}

const bool Field::hasXMinusWall() const
{
	return _hasXMinusWall;
}

void Field::setHasZMinusWall(const bool hasZMinusWall)
{
	_hasZMinusWall = hasZMinusWall;
}

void Field::setHasZPlusWall(const bool hasZPlusWall)
{
	_hasZPlusWall = hasZPlusWall;
}

void Field::setHasXPlusWall(const bool hasXPlusWall)
{
	_hasXPlusWall = hasXPlusWall;
}

void Field::setHasXMinusWall(const bool hasXMinusWall)
{
	_hasXMinusWall = hasXMinusWall;
}

const bool Field::isOnZMinusBorder() const
{
	return _isOnZMinusBorder;
}

const bool Field::isOnZPlusBorder() const
{
	return _isOnZPlusBorder;
}

const bool Field::isOnXPlusBorder() const
{
	return _isOnXPlusBorder;
}

const bool Field::isOnXMinusBorder() const
{
	return _isOnXMinusBorder;
}

void Field::setIsOnZMinusBorder(const bool isOnZMinusBorder)
{
	_isOnZMinusBorder = isOnZMinusBorder;
}

void Field::setIsOnZPlusBorder(const bool isOnZPlusBorder)
{
	_isOnZPlusBorder = isOnZPlusBorder;
}

void Field::setIsOnXPlusBorder(const bool isOnXPlusBorder)
{
	_isOnXPlusBorder = isOnXPlusBorder;
}

void Field::setIsOnXMinusBorder(const bool isOnXMinusBorder)
{
	_isOnXMinusBorder = isOnXMinusBorder;
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