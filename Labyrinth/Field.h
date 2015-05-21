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
	const bool hasZMinusWall() const;
	void setHasZMinusWall(const bool hasZMinusWall);

	const bool isOnZMinusBorder() const;
	void setIsOnZMinusBorder(const bool isOnZMinusBorder);

	/*
	Wall between (0, 0, qs) and (qs 0, qs), where qs is the quad size.
	*/
	const bool hasZPlusWall() const;
	void setHasZPlusWall(const bool hasZPlusWall);

	const bool isOnZPlusBorder() const;
	void setIsOnZPlusBorder(const bool isOnZPlusBorder);

	/*
	Wall between (qs, 0, 0) and (qs, 0, qs), where qs is the quad size.
	*/
	const bool hasXPlusWall() const;
	void setHasXPlusWall(const bool hasXPlusWall);

	const bool isOnXPlusBorder() const;
	void setIsOnXPlusBorder(const bool isOnXPlusBorder);

	/*
	Wall between (0, 0, 0) and (0, 0, qs), where qs is the quad size.
	*/
	const bool hasXMinusWall() const;
	void setHasXMinusWall(const bool hasXMinusWall);

	const bool isOnXMinusBorder() const;
	void setIsOnXMinusBorder(const bool isOnXMinusBorder);

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
	bool _hasZMinusWall = false;
	bool _hasZPlusWall = false;
	bool _hasXPlusWall = false;
	bool _hasXMinusWall = false;
		 
	bool _isOnZMinusBorder = false;
	bool _isOnZPlusBorder = false;
	bool _isOnXPlusBorder = false;
	bool _isOnXMinusBorder = false;
		 
	bool _hasCoin = false;
	bool _hasDiamond = false;

	PortalType _portal = NONE;
};