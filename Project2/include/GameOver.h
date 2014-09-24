//
// GameOver.h
//

#include "ViewObject.h"

class GameOver : public ViewObject {

 private:
  int time_to_live;
  void step();

 public:
  GameOver();
  ~GameOver();
  int eventHandler(Event *p_e);
  void draw();
};
