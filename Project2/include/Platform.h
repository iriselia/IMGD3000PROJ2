//
// Platform.h
//

#include "Object.h"
#include "EventStep.h"
#include "EventCollision.h"

#define PLATFORM_THIN '_'
#define PLATFORM_THICK '='
#define PLATFORM_THIN_WALL '|'
#define PLATFORM_THICK_WALL '"'

class Platform : public Object {

 private:
	 bool isItThick;
	 int size;
	 int height;
	 int move_countdown;
  void out();
  void step(EventStep *p_s);
  void hit(EventCollision *p_c);

 public:
  Platform();
  Platform(bool thickness, int sizee, int heightt, int x, int y, float x_speed, float y_speed);
  void draw(void);
  int eventHandler(Event *p_e);
};
