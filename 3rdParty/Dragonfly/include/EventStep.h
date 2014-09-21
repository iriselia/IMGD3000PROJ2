///
/// A "step" event, generated once per game loop.
///

#pragma once

#include "Event.h"

#define DF_STEP_EVENT "__step__"

class EventStep : public Event {

 private:
  int step_count;  /// Iteration number of game loop.
  
 public:
  /// Default constructor.
	 EventStep();
  
  /// Constructor with initial step count.
	 EventStep(int init_step_count);
  
  /// Set step count.
	 void setStepCount(int new_step_count)
	 {
		 step_count = new_step_count;
	 }

  /// Get step count.
	 int getStepCount() const
	 {
		 return step_count;
	 }
};
