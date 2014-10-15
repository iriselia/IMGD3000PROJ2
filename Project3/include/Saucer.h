//
// Saucer.h
//
 
#include "EventCollision.h"
#include "Object.h"
 
#define SAUCER_CHAR 'O'

class Saucer : public Object {
 
 private:
  void moveToStart();
  void out();
  void hit(EventCollision *p_c);

 public:
  Saucer();
  int eventHandler(Event *p_e);
  void draw();
};
