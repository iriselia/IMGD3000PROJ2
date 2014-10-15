#include "EventCollision.h"
#include "Object.h"

class MadSquare : public Object {

private:

	//void kbd(EventKeyboard *keyboard_event);

	void step();
	void activate(EventCollision* _eventCollision);
	//void fire();
	int fire_slowdown;
	int fire_countdown;
public:
	MadSquare();
	MadSquare(int x, int y);
	~MadSquare();
	void fire();
	int eventHandler(Event *p_e);
	void draw();
};
