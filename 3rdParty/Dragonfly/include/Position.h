///
/// A 2d (x,y) position
///

#pragma once

class Position
{

private:
	int x; 			///< Horizontal coordinate in 2d world.
	int y; 			///< Vertical coordinate in 2d world.

public:

	/// Create object at 2d location (x,y).  
	Position(int init_x, int init_y);

	/// Default 2d (x,y) location is (0,0).
	Position();

	int getX() const ///< Get horizontal coordinate.
	{
		return x;
	}
	void setX(int new_x) ///< Set horizontal coordinate.
	{
		x = new_x;
	}
	int getY()const ///< Get vertical coordinate.
	{
		return y;
	}
	void setY(int new_y)  ///< Set vertical coordinate.
	{
		y = new_y;
	}
	void setXY(int new_x, int new_y) ///< Set horizontal & vertical coord.
	{
		x = new_x;
		y = new_y;
	}
	bool operator==(Position &other) const; ///< Compare Positions.

	bool operator!=(Position &other) const; ///< Compare Positions.
};