//
// GameOver.h
//

#include "ViewObject.h"

class GameOverFlag : public ViewObject {

 private:
  int time_to_live;
  void step();

 public:
  GameOverFlag();
  ~GameOverFlag();
  int eventHandler(Event *p_e);
  void draw();
};
