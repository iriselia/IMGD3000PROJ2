///
/// Pause
/// 

#ifndef __PAUSE_H__
#define __PAUSE_H__

#include "Object.h"	

#define DF_PAUSE_KEY 274	///< Default pause is F10.

class Pause: public Object {
 private:
  int pause_key;		///< Pause key.

 public:
  Pause(int init_pause_key = DF_PAUSE_KEY);
  int eventHandler(Event *p_e);
};
 
#endif // __PAUSE_H__
