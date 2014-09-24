// Hero.h
//

#include "EventKeyboard.h"
#include "Object.h"

#define HERO_CHAR '>'

class Hero : public Object {

 private:
  int fire_slowdown;
  int fire_countdown;
  int nuke_count;
  void kbd(EventKeyboard *keyboard_event);
  void move(int dy);
  void fire();
  void step();
  void nuke();

 public:
  Hero();
  ~Hero();
  int eventHandler(Event *p_e);
  void draw();
};
