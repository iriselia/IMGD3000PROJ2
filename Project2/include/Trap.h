// Trap.h
//

#include "EventKeyboard.h"
#include "Object.h"

class Trap : public Object {

 private:

  //void kbd(EventKeyboard *keyboard_event);

  void step();
  void activate(EventCollision* _eventCollision);

 public:
  Trap();
  ~Trap();
  int eventHandler(Event *p_e);
  void draw();
};
