//
// GameOver.h
//

#include "ViewObject.h"

class GameWin : public ViewObject {

 private:
  int time_to_live;
  void step();

 public:
  GameWin();
  ~GameWin();
  int eventHandler(Event *p_e);
  void draw();
};
