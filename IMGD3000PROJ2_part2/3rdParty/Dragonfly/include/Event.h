///
/// The base event
///

#pragma once

#include <string>

#define DF_UNDEFINED_EVENT "__undefined__"

using std::string;

class Event {

 private:
  string event_type;      ///< Holds event type.

 public:
  /// Create base event.
	 Event()
	 {
		 event_type = DF_UNDEFINED_EVENT;
	 }

  /// Destructor.
	 virtual ~Event() {}

  /// Set event type.
  void setType(string new_type)
  {
	  event_type = new_type;
  }

  /// Get event type.
  string getType() const
  {
	  return event_type;
  }
}; 