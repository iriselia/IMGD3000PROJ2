#include "EventCollision.h"
#include "Object.h"

class MadSquare : public Object {

private:

	//void kbd(EventKeyboard *keyboard_event);

	void step();
	void activate(EventCollision* _eventCollision);

public:
	MadSquare();
	~MadSquare();
	int eventHandler(Event *p_e);
	void draw();
};
