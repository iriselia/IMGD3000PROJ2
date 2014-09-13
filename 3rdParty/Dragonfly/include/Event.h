///
/// The base event
///

#ifndef __EVENT_H__
#define __EVENT_H__

#include <string>

#define DF_UNDEFINED_EVENT "__undefined__"

using std::string;

class Event {

 private:
  string event_type;      ///< Holds event type.

 public:
  /// Create base event.
  Event();

  /// Destructor.
  virtual ~Event();

  /// Set event type.
  void setType(string new_type);  

  /// Get event type.
  string getType() const;
}; 

#endif // __EVENT_H__
