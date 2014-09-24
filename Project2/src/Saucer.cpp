//
// Saucer.cpp
//
 
#include <stdlib.h>		// for random()

// Engine includes.
#include "EventCollision.h"
#include "EventNuke.h"
#include "EventOut.h"
#include "GraphicsManager.h"
#include "LogManager.h"
#include "WorldManager.h"
 
// Game includes.
#include "Explosion.h"
#include "Saucer.h"

Saucer::Saucer() {
  LogManager &log_manager = LogManager::getInstance();

  // Set object type.
  setType("Saucer");

  // Set speed in vertical direction.
  setXVelocity(-0.25);		// 1 space every 4 frames

  moveToStart();

#ifdef REGISTER
  // Register interest in "nuke" event.
  registerInterest(NUKE_EVENT);
#endif 
}

// Handle event.
// Return 0 if ignored, else 1.
int Saucer::eventHandler(Event *p_e) {

  if (p_e->getType() == DF_OUT_EVENT) {
    out();
    return 1;
  }

  if (p_e->getType() == DF_COLLISION_EVENT) {
    EventCollision *p_collision_event = static_cast <EventCollision *> (p_e);
    hit(p_collision_event);
    return 1;
  }

  if (p_e->getType() == NUKE_EVENT) {
 
    // Create explosion.
    Explosion *p_explosion = new Explosion;
    p_explosion -> setPosition(this -> getPosition());
 
    // Delete self.
    WorldManager &world_manager = WorldManager::getInstance();
    world_manager.markForDelete(this);
 
    // Saucers appear stay around perpetually
    new Saucer;
  }
 
  // If get here, have ignored this event.
  return 0;
}

// If moved off left edge, move back to far right.
void Saucer::out() {

  // If haven't moved off left edge, then nothing to do.
  if (getPosition().getX() >= 0)
    return;

  // Otherwise, move back to far right.
  moveToStart();

  // Spawn new Saucer to make the game get harder.
  new Saucer;

}

// If saucer and player collide, mark both for deletion.
void Saucer::hit(EventCollision *p_c) {

  // If Saucer on Saucer, ignore.
  if ((p_c -> getObject1() -> getType() == "Saucer") &&
      (p_c -> getObject2() -> getType() == "Saucer"))
    return;

  // If Bullet ...
  if ((p_c -> getObject1() -> getType() == "Bullet") ||
      (p_c -> getObject2() -> getType() == "Bullet")) {

    // Create an explosion.
    Explosion *p_explosion = new Explosion;
    p_explosion -> setPosition(this -> getPosition());

    // Saucers appear stay around perpetually.
    new Saucer;
  }

  // If Hero, mark both objects for destruction.
  if (((p_c -> getObject1() -> getType()) == "Hero") || 
      ((p_c -> getObject2() -> getType()) == "Hero")) {
    WorldManager &world_manager = WorldManager::getInstance();
    world_manager.markForDelete(p_c -> getObject1());
    world_manager.markForDelete(p_c -> getObject2());
  }

}

// Move saucer to starting location on right side of screen.
void Saucer::moveToStart() {
  WorldManager &world_manager = WorldManager::getInstance();
  Position temp_pos;

  // Get world boundaries.
  int world_horiz = world_manager.getBoundary().getHorizontal();
  int world_vert = world_manager.getBoundary().getVertical();

  // x is off right side of screen.
  temp_pos.setX(world_horiz + random()%world_horiz + 3);

  // y is in vertical range.
  temp_pos.setY(random()%(world_vert-4) + 4);

  // If collision, move right slightly until empty space.
  ObjectList collision_list = world_manager.isCollision(this, temp_pos);
  while (!collision_list.isEmpty()) {
    temp_pos.setX(temp_pos.getX()+1);
    collision_list = world_manager.isCollision(this, temp_pos);
  }

  world_manager.moveObject(this, temp_pos);
}

void Saucer::draw() {
  GraphicsManager &graphics_manager = GraphicsManager::getInstance();
  graphics_manager.drawCh(getPosition(), SAUCER_CHAR, COLOR_GREEN); 
}
