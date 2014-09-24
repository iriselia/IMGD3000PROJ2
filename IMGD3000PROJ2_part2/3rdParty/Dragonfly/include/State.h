///
/// State.h
///

#ifndef STATE_H
#define STATE_H

#include "Object.h"

#define DF_UNDEFINED_STATE "__undefined state__"

class State {
 private:
  string state_type;      /// Name of state.

 public:
  State();

  /// Set name of state.
  void setType(string new_type);

  /// Get name of state.
  string getType() const;

  /// Invoked when state first entered.
  virtual void Enter(Object *p_obj);

  /// Invoked every game loop step.
  virtual void Execute(Object *p_obj)=0;

  /// Invoked when state exited.
  virtual void Exit(Object *p_obj);
};

#endif
