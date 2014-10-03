///
/// A sprite frame
///

#pragma once

#include <string>

using std::string;

class Frame
{

private:
	int width;          ///< Width of frame
	int height;         ///< Height of frame
	string frame_str;   ///< All frame characters stored as string.

public:
	/// Create empty frame.
	Frame()
	{
		width = 0;
		height = 0;
	}

	/// Create frame of indicated width and height with string.
	Frame(int new_width, int new_height, string frame_str)
	{
		width = new_width;
		height = new_height;
		this->frame_str = frame_str;
	}

	/// Set width of frame.
	void setWidth(int new_width)
	{
		width = new_width;
	}

	/// Get width of frame.
	int getWidth() const
	{
		return width;
	}

	/// Set height of frame.
	void setHeight(int new_height)
	{
		height = new_height;
	}

	/// Get height of frame.
	int getHeight() const
	{
		return height;
	}

	/// Set frame characters (stored as string).
	void setString(string new_frame_str)
	{
		this->frame_str = new_frame_str;
	}

	/// Get frame characters (stored as string).
	string getString() const
	{
		return frame_str;
	}
};
