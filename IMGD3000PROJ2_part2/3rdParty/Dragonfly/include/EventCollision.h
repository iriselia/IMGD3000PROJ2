///
/// A "collision" event
///

#ifndef __EVENT_COLLISION_H__
#define __EVENT_COLLISION_H__

#include "Event.h"
#include "Object.h"

#define DF_COLLISION_EVENT "__collision__"

class EventCollision : public Event
{

private:
	Position pos;          ///< Where collision occurred.
	Object *p_obj1;        ///< Object moving, causing collision.
	Object *p_obj2;        ///< Object being collided with.

public:
	/// Create collision event at (0,0) with obj1 and obj2 NULL.
	EventCollision()
	{
		setType(DF_COLLISION_EVENT);
	}

	/// Create collision event between o1 and o2 at position p.
	/// Object o1 "caused" collision by moving into object o2.
	EventCollision(Object *p_o1, Object *p_o2, Position p)
	{
		setType(DF_COLLISION_EVENT);
		pos = p;
		p_obj1 = p_o1;
		p_obj2 = p_o2;
	}

	/// Set object that caused collision.
	void setObject1(Object *p_new_o1)
	{
		p_obj1 = p_new_o1;
	}

	/// Return object that caused collision.
	Object *getObject1() const
	{
		return p_obj1;
	}

	/// Set object that was collided with.
	void setObject2(Object *p_new_o2)
	{
		p_obj2 = p_new_o2;
	}

	/// Return object that was collided with.
	Object *getObject2() const
	{
		return p_obj2;
	}

	/// Set position of collision.
	void setPosition(Position new_pos)
	{
		pos = new_pos;
	}

	/// Return position of collision.
	Position getPosition() const
	{
		return pos;
	}
};

#endif /// __EVENT_COLLISION_H__
