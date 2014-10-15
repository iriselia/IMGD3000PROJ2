// Trap.h
//

#include "EventKeyboard.h"
#include "Object.h"

class WinFlag : public Object {

 private:

  //void kbd(EventKeyboard *keyboard_event);

  void step();
  void activate(EventCollision* _eventCollision);

 public:
  WinFlag();
  WinFlag(int x, int y);
  ~WinFlag();
  int eventHandler(Event *p_e);
  void draw();
};
