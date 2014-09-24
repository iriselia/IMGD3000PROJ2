//
// Star.h
//

#include "Object.h"

#define STAR_CHAR '.'

class Star : public Object {

 private:
  void out();

 public:
  Star();
  void draw(void);
  int eventHandler(Event *p_e);
};
