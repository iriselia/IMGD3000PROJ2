///
/// An "out of bounds" event
///

#ifndef __EVENT_OUT_H__
#define __EVENT_OUT_H__

#include "Event.h"

#define DF_OUT_EVENT "__out__"

class EventOut : public Event
{

public:
	EventOut()
	{
		setType(DF_OUT_EVENT);
	}
};

#endif // __EVENT_OUT_H__
