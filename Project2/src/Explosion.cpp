//
// Explosion.cpp
//

// Engine includes.
#include "EventStep.h"
#include "GameManager.h"
#include "GraphicsManager.h"
#include "LogManager.h"
#include "WorldManager.h"

// Game includes.
#include "Explosion.h"

Explosion::Explosion() {
  setType("Explosion");

  // Exit after about 6 steps.
  time_to_live =  6; 

  // Doesn't collide
  setSolidness(SPECTRAL);

#ifdef REGISTER
  // Need step event to countdown.
  registerInterest(DF_STEP_EVENT);
#endif

}

// Handle event.
// Return 0 if ignored, else 1.
int Explosion::eventHandler(Event *p_e) {

  if (p_e->getType() == DF_STEP_EVENT) {
    step();
    return 1;
  }

  // If get here, have ignored this event.
  return 0;
}

// Count down until explosion finished.
void Explosion::step() {
  time_to_live--;
  if (time_to_live <= 0){
    WorldManager &world_manager = WorldManager::getInstance();
    world_manager.markForDelete(this);
  }
}

void Explosion::draw() {
  GraphicsManager &graphics_manager = GraphicsManager::getInstance();
  graphics_manager.drawCh(getPosition(), '*', COLOR_RED); 

  if (time_to_live < 4) {
    Position p1(getPosition().getX()-1, getPosition().getY()-1);
    Position p2(getPosition().getX()+1, getPosition().getY()-1);
    Position p3(getPosition().getX()-1, getPosition().getY()+1);
    Position p4(getPosition().getX()+1, getPosition().getY()+1);
    graphics_manager.drawCh(p1, '\\', COLOR_RED); 
    graphics_manager.drawCh(p2, '/', COLOR_RED); 
    graphics_manager.drawCh(p3, '/', COLOR_RED); 
    graphics_manager.drawCh(p4, '\\', COLOR_RED); 
  }
}
