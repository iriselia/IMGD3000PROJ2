///
/// The clock, for timing
///

#ifndef __CLOCK_H__
#define __CLOCK_H__

#include <time.h>

class Clock {

 private:
  struct timespec prev_ts;  /// Store previous time called.

 public:
  /// Sets prev_ts to current time.
  Clock();

  /// Return time elapsed since delta() was called.
  /// Units are microseconds.
  /// Return -1 if error.
  long int delta(void);

  /// Return time elapsed since delta() was last called.
  /// Units are microseconds.
  /// Return -1 if error.
  long int split(void) const;
};

#endif // __CLOCK_H__
