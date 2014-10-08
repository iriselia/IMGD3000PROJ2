//
// Platform.h
//

#include "Object.h"

#define PLATFORM_THIN '_'
#define PLATFORM_THICK '='

class Platform : public Object {

 private:
	 bool isItThick;
	 int size;
  void out();
  void hit(EventCollision *p_c);

 public:
  Platform();
  void draw(void);
  int eventHandler(Event *p_e);
};
