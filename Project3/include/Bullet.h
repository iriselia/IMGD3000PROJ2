//
// Bullet.h
//

#include "EventCollision.h"
#include "Object.h"

#define BULLET_CHAR '-'
enum direction{
	NORTH, SOUTH, EAST, WEST, E_W, N_S, NSEW
};
class Bullet : public Object {

 private:
	 int type;
  void out();
  void hit(EventCollision *p_c);

 public:
	 Bullet(Position hero_pos, int velocityX);
	 Bullet(Position hero_pos, int velocityX, int velocityY, int typee);
  int eventHandler(Event *p_e);
  void draw();
};
