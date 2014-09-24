///
/// Dragonfly for splash screen
/// 

#ifndef __SPLASH_DRAGONFLY_H__
#define __SPLASH_DRAGONFLY_H__

#include "EventStep.h"
#include "Object.h"	

class SplashDragonfly : public Object {

 private:
  Position end_position;  /// Ending position of Object.
  int countdown;          /// Countdown to event actions.

 public:
  SplashDragonfly(Position p);
  ~SplashDragonfly();
  int eventHandler(Event *p_e);
};
 
#endif // __SPLASH_DRAGONFLY_H__
