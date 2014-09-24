///
/// A 2-d bounding box
///

#pragma once

#include "Position.h"

class Box {

 private:
  Position corner;         ///< Upper left corner of box.
  int horizontal;          ///< Horizontal dimension.
  int vertical;            ///< Vertical dimension.

 public:
  /// Create box with upper-left corner, horiz and vert sizes.
	 Box(Position init_corner, int init_horizontal, int init_vertical);

  /// Create box with (0,0) for corner, and 0 for horiz and vert.
	 Box();

  /// Set upper left corner of box.
	 void setCorner(Position new_corner)
	 {
		 corner = new_corner;
	 }

  /// Get upper left corner of box.
	 Position getCorner() const
	 {
		 return corner;
	 }

  /// Set horizontal size of box.
	 void setHorizontal(int new_horizontal)
	 {
		 horizontal = new_horizontal;
	 }

  /// Get horizontal size of box.
	 int getHorizontal() const
	 {
		 return horizontal;
	 }

  /// Set vertical size of box.
	 void setVertical(int new_vertical)
	 {
		 vertical = new_vertical;
	 }

  /// Get vertical size of box.
	 int getVertical() const
	 {
		 return vertical;
	 }

	 bool operator==(Box &other) const ///< Compare boxes.
	 {
		 return corner == other.corner &&
			 horizontal == other.horizontal &&
			 vertical == other.vertical;
	 }

	 bool operator!=(Box &other) const ///< Compare boxes.
	 {
		 return !this->operator==(other);
	 }
};
