///
/// A sprite frame
///

#ifndef __FRAME_H__
#define __FRAME_H__

#include <string>

using std::string;

class Frame {

 private:
  int width;          ///< Width of frame
  int height;         ///< Height of frame
  string frame_str;   ///< All frame characters stored as string.

 public:
  /// Create empty frame.
  Frame();

  /// Create frame of indicated width and height with string.
  Frame(int new_width, int new_height, string frame_str);

  /// Set width of frame.
  void setWidth(int new_width);

  /// Get width of frame.
  int getWidth() const;

  /// Set height of frame.
  void setHeight(int new_height);

  /// Get height of frame.
  int getHeight() const;

  /// Set frame characters (stored as string).
  void setString(string new_frame_str);

  /// Get frame characters (stored as string).
  string getString() const;
};

#endif //__FRAME_H__
