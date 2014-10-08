// Hero.h
//

#include "EventKeyboard.h"
#include "EventMouse.h"
#include "EventCollision.h"
#include "Object.h"

#define HERO_CHAR '>'

class Hero : public Object
{

private:
	enum HeroState
	{
		WalkLeft = 0x1,
		WalkRight = 0x10,
		Jump = 0x100,
		Shoot = 0x1000
	};

	int fire_slowdown;
	int fire_countdown;
	int nuke_count;
	void kbd(EventKeyboard *keyboard_event);
	void mouse(EventMouse* mouse_event);
	void move(int dy);
	void fire();
	void step();
	void nuke();
	void jump();
	void processCollision(EventCollision* _p_collision_event);
	int m_state;

public:
	Hero();
	~Hero();
	int eventHandler(Event *p_e);
	void draw();
	void switchAnimation();
};
