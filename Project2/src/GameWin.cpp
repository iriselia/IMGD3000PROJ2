//
// GameOver.cpp
//

// Engine includes.
#include "EventStep.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "GameManager.h"

// Game includes.
#include "GameWin.h"
#include "EventKeyboard.h"

GameWin::GameWin()
{

	setType("GameOver");

	// Link to "message" sprite.
	ResourceManager &resource_manager = ResourceManager::getInstance();
	Sprite *p_temp_sprite = resource_manager.getSprite("gamewin");
	if (!p_temp_sprite)
	{
		LogManager &log_manager = LogManager::getInstance();
		log_manager.writeLog("GameOver::GameOver(): Warning! Sprite 'gameover' not found");
	}
	else
	{
		setSprite(p_temp_sprite);
		setSpriteSlowdown(15);
		setTransparency('#');    // Transparent character.
		time_to_live = p_temp_sprite->getFrameCount() * 15;
	}

	// Put in center of screen.
	setLocation(CENTER_CENTER);
	setPosition(viewToWorld(getPosition()));

	// Register for step event.
	registerInterest(DF_STEP_EVENT);
}

// When done, game over.
GameWin::~GameWin()
{
	WorldManager &world_manager = WorldManager::getInstance();

	world_manager.setViewPosition(Position(0, 0));

	// Remove Saucers and ViewObjects, re-activate GameStart.
	ObjectList object_list = world_manager.getAllObjects();
	ObjectListIterator i(&object_list);
	for (i.first(); !i.isDone(); i.next())
	{
		Object *p_o = i.currentObject();
		if (p_o->getType() != "GameStart")
		{
			world_manager.markForDelete(p_o);
			p_o->setActive(false);
		}
		if (p_o->getType() == "GameStart")
		{
//			p_o->setPosition(viewToWorld(p_o->getPosition()));
			p_o->setActive(true);
		}
	}
}

// Handle event.
// Return 0 if ignored, else 1.
int GameWin::eventHandler(Event *p_e)
{
	WorldManager &world_manager = WorldManager::getInstance();
	GameManager& gameMgr = GameManager::getInstance();

	if (p_e->getType() == DF_STEP_EVENT)
	{
		step();
		return 1;
	}

	if (p_e->getType() == DF_KEYBOARD_EVENT)
	{
		EventKeyboard *p_keyboard_event = (EventKeyboard *)p_e;
		switch (p_keyboard_event->getKey())
		{
		case 'p': 			// play
			world_manager.markForDelete(this);
			break;
		case 'q':			// quit
			gameMgr.setGameOver();
			break;
		default:
			break;
		}
		return 1;
	}

	// If get here, have ignored this event.
	return 0;
}

// Count down to end of message.
void GameWin::step()
{
	time_to_live--;
	if (time_to_live <= 0)
	{
		//WorldManager &world_manager = WorldManager::getInstance();
		//world_manager.markForDelete(this);
	}
}

// Override default draw so as not to display "value".
void GameWin::draw()
{
	Object::draw();
}
