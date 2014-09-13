///
/// The graphics manager
///

#ifndef __GRAPHICS_MANAGER_H__
#define __GRAPHICS_MANAGER_H__

#ifdef CYGWIN
#include <ncurses/curses.h>
#else
#include <curses.h>
#endif

/// Supports colors, defined by curses:
///   COLOR_BLACK ("black" in Sprite file)
///   COLOR_RED ("red" in Sprite file)
///   COLOR_GREEN ("green" in Sprite file)
///   COLOR_YELLOW ("yellow" in Sprite file)
///   COLOR_BLUE ("blue" in Sprite file)
///   COLOR_MAGENTA ("magenta" in Sprite file)
///   COLOR_CYAN ("cyan" in Sprite file)
///   COLOR_WHITE ("white" in Sprite file)

#define DF_COLOR_DEFAULT COLOR_WHITE ///< If color not specified, will use this.

#include "Manager.h"
#include "Position.h"
#include "Frame.h"

enum Justification {
  LEFT_JUSTIFIED,
  CENTER_JUSTIFIED,
  RIGHT_JUSTIFIED,
};

class GraphicsManager : public Manager {

 private:
  GraphicsManager();                        ///< Private since a singleton.
  GraphicsManager (GraphicsManager const&); ///< Don't allow copy.
  void operator=(GraphicsManager const&);   ///< Don't allow assignment.
  WINDOW *buffer1;                          ///< Allocated drawing buffer 1.
  WINDOW *buffer2;                          ///< Allocated drawing buffer 2.
  WINDOW *p_buffer;                ///< Pointer to current drawing buffer.

 public:
  /// Get the one and only instance of the GraphicsManager.
  static GraphicsManager &getInstance();

  /// Get terminal ready for text-based display.
  /// Return 0 if ok, else return negative number.
  int startUp();

  /// Revert back to normal terminal display.
  void shutDown();

  /// Draw character at screen location (x,y) with color.
  /// Return 0 if ok, else -1.
  int drawCh(Position world_pos, char ch, int color=DF_COLOR_DEFAULT) const;

  /// Draw single sprite frame at screen location (x,y) with color.
  /// If centered true, then center frame at (x,y).
  /// Don't draw transparent characters (0 means none).
  /// Return 0 if ok, else -1.
  int drawFrame(Position world_pos, Frame frame, bool centered, 
                char transparent, int color=DF_COLOR_DEFAULT) const;

  /// Draw string at screen location (x,y) with color.
  /// Justified left, center or right.
  /// Return 0 if ok, else -1.
  int drawString(Position world_pos, string str, Justification just, 
                 int color=DF_COLOR_DEFAULT) const;

  /// Return display's horizontal maximum.
  int getHorizontal() const;

  /// Return display's vertical maximum.
  int getVertical() const;

  /// Render current display buffer.
  /// Return 0 if ok, else -1.
  int swapBuffers();

  /// Return curses window that has been most recently drawn and refreshed.
  WINDOW *getPreviousBuffer() const;
 
  /// Return curses window that is being drawn to but not yet refreshed.
  WINDOW *getCurrentBuffer() const;
};
#endif //__GRAPHICS_MANAGER_H__
