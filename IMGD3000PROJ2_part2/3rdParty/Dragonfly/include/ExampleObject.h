#pragma once
#include "Object.h"

class ExampleObject : public Object
{
public:
	ExampleObject();
	virtual ~ExampleObject();
	virtual int eventHandler(Event *p_event);
protected:
private:
};