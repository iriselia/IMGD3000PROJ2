//
// Platform.h
//

#include "Object.h"

#define PLATFORM_THIN '_'
#define PLATFORM_THICK '='
#define PLATFORM_THIN_WALL '|'
#define PLATFORM_THICK_WALL '"'

class Platform : public Object {

 private:
	 bool isItThick;
	 int size;
	 int height;
  void out();
  void step(EventStep *p_s);
  void hit(EventCollision *p_c);

 public:
  Platform();
  Platform(bool thickness, int sizee, int heightt, int x, int y);
  void draw(void);
  int eventHandler(Event *p_e);
};
