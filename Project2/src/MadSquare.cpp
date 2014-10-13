//
// MadSquare.cpp
//

// Engine includes.
#include "EventStep.h"
#include "GraphicsManager.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"

// Game includes.
#include "Explosion.h"
#include "Bullet.h"
#include "EventCollision.h"
#include "MadSquare.h"


MadSquare::MadSquare()
{

	LogManager &log_manager = LogManager::getInstance();

#ifdef REGISTER
	// Player controls hero, so register with keyboard.
	registerInterest(DF_KEYBOARD_EVENT);

	// Need to update fire rate control each step.
	registerInterest(DF_STEP_EVENT);
#endif

	// Set object type.
	setType("MadSquare");
	auto& resMgr = ResourceManager::getInstance();
	setSprite(resMgr.getSprite("madsquare"));
	setSpriteSlowdown(4);
	setAltitude(1);
	// Set starting location.
	WorldManager &world_manager = WorldManager::getInstance();
	Position pos(7, world_manager.getBoundary().getVertical() / 2);
	setPosition(Position(45, 10));
	setBox(Box(Position(0, 0), getSprite()->getWidth(), getSprite()->getHeight()));
	//setYVelocity(0.25);
	// Set firing variables.
	fire_slowdown = 15;
	fire_countdown = fire_slowdown;
}

MadSquare::~MadSquare()
{
	if (isActive())
	{

		Position temp_pos = this->getPosition();
		temp_pos.setX(this->getPosition().getX());
		temp_pos.setY(this->getPosition().getY());
		Explosion *p_explosion = new Explosion;
		p_explosion->setPosition(temp_pos);
	}
}

void MadSquare::fire()
{
	if (fire_countdown > 0)
		return;
	fire_countdown = fire_slowdown;
	int bulletVel = 3;
	new Bullet(getPosition(), bulletVel);

}
// Handle event.
// Return 0 if ignored, else 1.
int MadSquare::eventHandler(Event *p_e)
{
	if (p_e->getType() == DF_STEP_EVENT)
	{
		step();
		return 1;
	}

	if (p_e->getType() == DF_COLLISION_EVENT)
	{
		EventCollision *p_collision_event = static_cast <EventCollision *> (p_e);
		activate(p_collision_event);
		return 1;
	}

	// If get here, have ignored this event.
	return 0;
}

// Decrease fire restriction.
void MadSquare::step()
{}

void MadSquare::draw()
{
	Object::draw();
	GraphicsManager &graphics_manager = GraphicsManager::getInstance();
	Box box = getBox();
	std::stringstream curPos;
	curPos << "Hero Position: " << getPosition().getX() << " , " << getPosition().getY() << " ";
	curPos << "Height: " << box.getVertical() << " , " << "Width: " << box.getHorizontal();
	/*	graphics_manager.drawString(Position(0, 24), curPos.str(), LEFT_JUSTIFIED);*/
	//   GraphicsManager &graphics_manager = GraphicsManager::getInstance();
	//   graphics_manager.drawCh(getPosition(), HERO_CHAR, COLOR_BLUE); 
}

void MadSquare::activate(EventCollision* _eventCollision)
{
	auto a = _eventCollision->getObject1();
	// If Hero, mark both objects for destruction.
	if (((_eventCollision->getObject1()->getType()) == "Hero") ||
		((_eventCollision->getObject2()->getType()) == "Hero"))
	{
		WorldManager &world_manager = WorldManager::getInstance();
		world_manager.markForDelete(_eventCollision->getObject1());
		world_manager.markForDelete(_eventCollision->getObject2());
	}
}
