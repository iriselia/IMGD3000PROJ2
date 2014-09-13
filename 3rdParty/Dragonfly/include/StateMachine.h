///
/// StateMachine.h
///

#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include "Object.h"
#include "State.h"

class StateMachine {

 private:
  Object *p_owner;         /// Owner of this state machine.
  State *p_state;          /// Current state.
  State *p_previous_state; /// Previous state.
  State *p_global_state;   /// Global state (reachable from any state).

 public:
  StateMachine();

  /// Set owner of state machine.
  void setOwner(Object *p_new_owner);

  /// Get owner of state machine.
  Object *getOwner() const;

  /// Set current state.
  void setState(State *p_new_state);

  /// Get current state.
  State *getState() const;

  /// Set previous state.
  void setPreviousState(State *p_new_state);

  /// Get previous state.
  State *getPreviousState() const;

  /// Set global state.
  void setGlobalState(State *p_new_state);

  /// Get global state.
  State *getGlobalState() const;

  /// Update state machine (calling Execute() for current state).
  void Update();

  /// Change current state.
  void changeState(State *p_new_state);

  /// Revert to previous state.
  void revertToPrevious();
};
#endif
