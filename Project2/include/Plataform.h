//
// Plataform.h
//

#include "Object.h"

//#define Plataform_CHAR '.'

class Plataform : public Object {

 private:
  void out();

 public:
  Plataform();
  void draw(void);
  int eventHandler(Event *p_e);
};
