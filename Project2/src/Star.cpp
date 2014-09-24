//
// Star.cpp
//

#include <stdlib.h>		// for random

// Engine includes.
#include "EventOut.h"
#include "GraphicsManager.h"
#include "WorldManager.h"

// Game includes.
#include "Star.h"

Star::Star() {
  setType("Star");
  setSolidness(SPECTRAL);
  setXVelocity(-1.0 / (random()%10 + 1));
  setAltitude(0);	// Make them in the background.
  WorldManager &world_manager = WorldManager::getInstance();
  Position pos(random()%world_manager.getBoundary().getHorizontal(),
	       random()%world_manager.getBoundary().getVertical());
  setPosition(pos);
}

void Star::draw() {
  GraphicsManager &graphics_manager = GraphicsManager::getInstance();
  graphics_manager.drawCh(getPosition(), STAR_CHAR); 
}

// Handle event.
// Return 0 if ignored, else 1.
int Star::eventHandler(Event *p_e) {

  if (p_e->getType() == DF_OUT_EVENT) {
    out();
    return 1;
  }

  // If get here, have ignored this event.
  return 0;
}

// If Star moved off screen, move back to far right.
void Star::out() {
  WorldManager &world_manager = WorldManager::getInstance();
  Position pos(world_manager.getBoundary().getHorizontal() + random()%20,
	       random() % world_manager.getBoundary().getVertical());
  setPosition(pos);
  setXVelocity(-1.0 / (random()%10 + 1));
}
