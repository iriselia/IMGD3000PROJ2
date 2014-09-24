#include "Position.h"

bool Position::operator!=(Position &other) const ///< Compare Positions.
{
	return !this->operator==(other);
}

bool Position::operator==(Position &other) const ///< Compare Positions.
{
	return (other.x == x) && (other.y == y);
}

Position::Position()
{
	x = 0;
	y = 0;
}

Position::Position(int init_x, int init_y)
{
	x = init_x;
	y = init_y;
}
