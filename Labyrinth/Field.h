#pragma once

class Field
{
public:

	enum PortalType
	{
		START, END, NONE
	};

	// TODO refactor the wall setter with enum

	/*
	Wall between (0, 0, 0) and (qs, 0, 0), where qs is the quad size.
	*/
	const bool hasLeftWall() const;
	void setHasLeftWall(const bool hasLeftWall);

	const bool isOnLeftBorder() const;
	void setIsOnLeftBorder(const bool isOnLeftBorder);

	/*
	Wall between (0, 0, qs) and (qs 0, qs), where qs is the quad size.
	*/
	const bool hasRightWall() const;
	void setHasRightWall(const bool hasRightWall);

	const bool isOnRightBorder() const;
	void setIsOnRightBorder(const bool isOnRightBorder);

	/*
	Wall between (qs, 0, 0) and (qs, 0, qs), where qs is the quad size.
	*/
	const bool hasUpperWall() const;
	void setHasUpperWall(const bool hasUpperWall);

	const bool isOnUpperBorder() const;
	void setIsOnUpperBorder(const bool isOnUpperBorder);

	/*
	Wall between (0, 0, 0) and (0, 0, qs), where qs is the quad size.
	*/
	const bool hasLowerWall() const;
	void setHasLowerWall(const bool hasLowerWall);

	const bool isOnLowerBorder() const;
	void setIsOnLowerBorder(const bool isOnLowerBorder);

	/*
	Returns true if the field contains a coin.
	*/
	const bool hasCoin() const;
	void setHasCoin(const bool hasCoin);

	/*
	Returns true if the field contains a diamond.
	*/
	const bool hasDiamond() const;
	void setHasDiamond(const bool hasDiamond);

	/*
	Returns true if the field contains the specified portal.
	*/
	const bool hasPortal(const PortalType type) const;
	void setHasPortal(const PortalType type);

private:
	bool _hasLeftWall = false;
	bool _hasRightWall = false;
	bool _hasUpperWall = false;
	bool _hasLowerWall = false;
		 
	bool _isOnLeftBorder = false;
	bool _isOnRightBorder = false;
	bool _isOnUpperBorder = false;
	bool _isOnLowerBorder = false;
		 
	bool _hasCoin = false;
	bool _hasDiamond = false;

	PortalType _portal = NONE;
};