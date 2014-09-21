#include "EventStep.h"

EventStep::EventStep(int init_step_count)
{
	this->setType(DF_STEP_EVENT);
	step_count = init_step_count;
}

EventStep::EventStep()
{
	this->setType(DF_STEP_EVENT);
	step_count = 0;
}

