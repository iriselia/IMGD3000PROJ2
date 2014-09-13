///
/// The resource manager
///

#ifndef __RESOURCE_MANAGER_H__
#define __RESOURCE_MANAGER_H__

#include <string>

#include "Manager.h"
#include "Sprite.h"

// Maximum number of unique sprites in game.
#define DF_MAX_SPRITES 10000

// Delimiters used to parse Sprite files -
// the ResourceManager "knows" file format.
#define DF_FRAMES_TOKEN "frames"
#define DF_HEIGHT_TOKEN "height"
#define DF_WIDTH_TOKEN "width"
#define DF_COLOR_TOKEN "color"
#define DF_END_FRAME_TOKEN "end"
#define DF_END_SPRITE_TOKEN "eof"

using std::string;

class ResourceManager : public Manager {

 private:
  ResourceManager (ResourceManager const&); ///< Don't allow copy.
  void operator=(ResourceManager const&);   ///< Don't allow assignment.
  ResourceManager();                        ///< Private since a singleton.
  Sprite *p_sprite[DF_MAX_SPRITES];       ///< Array of (pointers to) Sprites.
  int sprite_count;              ///< Count of number of loaded sprites.

 public:
  /// Get the one and only instance of the ResourceManager.
  static ResourceManager &getInstance();

  /// Get manager ready for resources.
  int startUp();

  /// Shut down manager, freeing up any allocated Sprites.
  void shutDown();

  /// Load Sprite from file.
  /// Assign indicated label to Sprite.
  /// Return 0 if ok, else -1.
  int loadSprite(string filename, string label);

  /// Unload Sprite with indicated label.
  /// Return 0 if ok, else -1.
  int unloadSprite(string label);

  /// Find Sprite with indicated label.
  /// Return pointer to it if found, else NULL.
  Sprite *getSprite(string label) const;
};

#endif //__RESOURCE_MANAGER_H__
