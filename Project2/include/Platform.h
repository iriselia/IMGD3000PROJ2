//
// Platform.h
//

#include "Object.h"

//#define Platform_CHAR '.'

class Platform : public Object {

 private:
  void out();
  void hit(EventCollision *p_c);

 public:
  Platform();
  void draw(void);
  int eventHandler(Event *p_e);
};
