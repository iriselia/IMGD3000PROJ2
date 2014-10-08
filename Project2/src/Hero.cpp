//
// Hero.cpp
//

// Engine includes.
#include "EventStep.h"
#include "GraphicsManager.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"

// Game includes.
#include "Bullet.h"
#include "EventNuke.h"
#include "Explosion.h"
#include "GameOver.h"
#include "EventCollision.h"
#include "Hero.h"

Hero::Hero()
{

	LogManager &log_manager = LogManager::getInstance();

#ifdef REGISTER
	// Player controls hero, so register with keyboard.
	registerInterest(DF_KEYBOARD_EVENT);

	// Need to update fire rate control each step.
	registerInterest(DF_STEP_EVENT);
#endif

	// Set object type.
	setType("Hero");
	auto& resMgr = ResourceManager::getInstance();
	m_state = HeroState::WalkRight;
	setSprite(resMgr.getSprite("hero_walk_right"));
	setSpriteSlowdown(4);

	// Set starting location.
	WorldManager &world_manager = WorldManager::getInstance();
	Position pos(7, world_manager.getBoundary().getVertical() / 2);
	setPosition(Position(5, 10));
	setBox(Box(Position(0, 0), getSprite()->getWidth(), getSprite()->getHeight()));
	world_manager.setViewFollowing(this);
	//setYVelocity(0.25);
	// Set firing variables.
	fire_slowdown = 15;
	fire_countdown = fire_slowdown;

	nuke_count = 1;
}

Hero::~Hero()
{

	// Create GameOver object.
	GameOver *p_go = new GameOver;

	// Make big explosion.
	for (int i = -8; i <= 8; i += 5)
	{
		for (int j = -5; j <= 5; j += 3)
		{
			Position temp_pos = this->getPosition();
			temp_pos.setX(this->getPosition().getX() + i);
			temp_pos.setY(this->getPosition().getY() + j);
			Explosion *p_explosion = new Explosion;
			p_explosion->setPosition(temp_pos);
		}
	}
}

// Handle event.
// Return 0 if ignored, else 1.
int Hero::eventHandler(Event *p_e)
{

	if (p_e->getType() == DF_KEYBOARD_EVENT)
	{
		EventKeyboard *p_keyboard_event = static_cast <EventKeyboard *> (p_e);
		kbd(p_keyboard_event);
		return 1;
	}

	if (p_e->getType() == DF_STEP_EVENT)
	{
		step();
		return 1;
	}

	if (p_e->getType() == DF_COLLISION_EVENT)
	{
		EventCollision *p_collision_event = static_cast <EventCollision *> (p_e);
		processCollision(p_collision_event);
		return 1;
	}

	// If get here, have ignored this event.
	return 0;
}

// Take appropriate action according to key pressed.
void Hero::kbd(EventKeyboard *p_keyboard_event)
{
	WorldManager &world_manager = WorldManager::getInstance();

	switch (p_keyboard_event->getKey())
	{
	case ' ':          // fire
		fire();
		break;
	case 13:	     // nuke!
		nuke();
		break;
	case 'q':          // quit
		world_manager.markForDelete(this);
		break;
	default:
		move(p_keyboard_event->getKey());
		//no break here
	};

	return;
}

void Hero::move(int dy)
{
	WorldManager &world_manager = WorldManager::getInstance();
	int x = getPosition().getX();
	int y = getPosition().getY();
	Position new_pos(getPosition().getX(), getPosition().getY());

	switch (dy)
	{
	case KEY_UP:       // up arrow
		jump();
		break;
	case KEY_DOWN:     // down arrow
		new_pos.setY(y + 1);
		break;
	case KEY_RIGHT:       // right arrow
		m_state &= ~HeroState::WalkLeft;
		m_state |= HeroState::WalkRight;
		new_pos.setX(x + 1);
		break;
	case KEY_LEFT:     // left arrow
		m_state &= ~HeroState::WalkRight;
		m_state |= HeroState::WalkLeft;
		new_pos.setX(x - 1);
		break;
	default:
		break;
	}
	switchAnimation();
	// If stays on screen, allow move.
 	if ((new_pos.getY() > 0) &&
 		(new_pos.getY() < (world_manager.getBoundary().getVertical() - 1)) &&
		(new_pos.getX() > 1))
	world_manager.moveObject(this, new_pos);
}

// Fire bullet.
void Hero::fire()
{
	if (fire_countdown > 0)
		return;
	fire_countdown = fire_slowdown;
	new Bullet(getPosition());
}

// Decrease fire restriction.
void Hero::step()
{
	//apply gravity
	float currYVel = getYVelocity();
	setYVelocity(currYVel + 0.098f);

	fire_countdown--;
	if (fire_countdown < 0)
		fire_countdown = 0;
}

// Send nuke event to all objects.
void Hero::nuke()
{

	// Check if nukes left.
	if (!nuke_count)
		return;
	nuke_count--;

	// Create "nuke" event and send to interested.
	WorldManager &world_manager = WorldManager::getInstance();
	EventNuke nuke;
	world_manager.onEvent(&nuke);
}

// 
void Hero::draw()
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

void Hero::jump()
{
	if (!(m_state & HeroState::Jump))
	{
		//apply gravity
		float currYVel = getYVelocity();
		setYVelocity(-1.5f);
		m_state |= HeroState::Jump;
	}
}

void Hero::processCollision(EventCollision* _p_c)
{
	if ((_p_c->getObject1()->getType() == "Platform") ||
		(_p_c->getObject2()->getType() == "Platform"))
	{
		// TODO: where are we relative to the platform?
		m_state &= ~HeroState::Jump;
		setYVelocity(.0f);
	}
}

void Hero::switchAnimation()
{
	auto& resMgr = ResourceManager::getInstance();
	if (m_state & HeroState::Jump)
	{
		setSprite(resMgr.getSprite("hero_jump"));
	}
	else if (m_state & HeroState::WalkLeft)
	{
		setSprite(resMgr.getSprite("hero_walk_left"));
	}
	else if (m_state & HeroState::WalkRight)
	{
		setSprite(resMgr.getSprite("hero_walk_right"));
	}
}
