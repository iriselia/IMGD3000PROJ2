#include "Box.h"

Box::Box()
{
	horizontal = 0;
	vertical = 0;
}

Box::Box(Position init_corner, int init_horizontal, int init_vertical)
{
	corner = init_corner;
	horizontal = init_horizontal;
	vertical = init_vertical;
}

