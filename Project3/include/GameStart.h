//
// GameStart.h
//

#include "ViewObject.h"

class GameStart : public ViewObject {

 private:
  void step();
  void start();

 public:
  GameStart();
  int eventHandler(Event *e);
  void draw();
};
