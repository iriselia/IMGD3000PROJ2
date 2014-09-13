///
/// The sprite
/// 

#ifndef __SPRITE_H__
#define __SPRITE_H__

#include <string>
#include "Frame.h"

using std::string;

class Sprite {

 private:
  int width;            ///< Sprite width.
  int height;           ///< Sprite height.
  int max_frame_count;  ///< Maximum number of frames sprite can have.
  int frame_count;      ///< Actual number of frames sprite has.
  int color;            ///< Optional color for entire sprite.
  Frame *frame;         ///< Array of frames.
  string label;         ///< Text label to identify sprite.
  Sprite();             ///< Sprite constructor always has one arg.

 public:
  /// Delete sprite, removing any allocated frames.
  ~Sprite();

  /// Create sprite with indicated maximum number of frames.
  Sprite(int max_frames);  

  /// Set width of sprite.
  void setWidth(int new_width);

  /// Get width of sprite.
  int getWidth() const;

  /// Set height of sprite.
  void setHeight(int new_height);

  /// Get height of sprite.
  int getHeight() const;

  /// Set sprite color.
  void setColor(int new_color);

  /// Get sprite color.
  int getColor() const;

  /// Get total count of frames in sprite.
  int getFrameCount() const;

  /// Get next sprite frame indicated by number.
  /// Return empty frame if out of range [0, frame_count].
  Frame getFrame(int frame_number) const;

  /// Add frame to sprite.
  /// Return -1 if frame array full, else 0.
  int addFrame(Frame new_frame);

  /// Set label associated with sprite.
  void setLabel(string new_label);

  /// Get label associated with sprite.
  string getLabel() const;
};

#endif // __SPRITE_H__
