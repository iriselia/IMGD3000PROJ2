///
/// The game manager
///

#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

#include <time.h>                     ///< For time_t.
#include "Manager.h"

#define DF_VERSION 3.0
 
#define DF_DEFAULT_FRAME_TIME 33      ///< In milliseconds (33 ms == 30 fps).

class GameManager : public Manager {

 private:
  GameManager();                      ///< Private since a singleton.
  GameManager (GameManager const&);   ///< Don't allow copy.
  void operator=(GameManager const&); ///< Don't allow assignment.
  bool game_over;           ///< True -> game loop should stop.
  int frame_time;           ///< Target time per game loop, in millisec.
  int step_count;           ///< Count game loop iterations.
  
 public:
  /// Get the singleton instance of the GameManager.
  static GameManager &getInstance();

  /// Startup all GameManager services.
  /// seed = random seed (default is seed with system time).
  int startUp(time_t seed=0);

  /// Game manager only accepts step events.
  /// Return false if other event.
  bool isValid(string event_name) const;

  /// Shut down GameManager services.
  void shutDown();

  /// Run game loop.
  /// frame_time is target time for 1 game loop.
  void run(int frame_time=DF_DEFAULT_FRAME_TIME);

  /// Set game over status to indicated value.
  /// If true (default), will stop game loop.
  void setGameOver(bool new_game_over=true);

  /// Get game over status.
  bool getGameOver() const;

  /// Return frame time.  
  /// Frame time is target time for each game loop, in milliseconds.
  int getFrameTime() const;
  
  /// Return game loop step count.
  int getStepCount() const;
};

#endif // __GAME_MANAGER_H__
