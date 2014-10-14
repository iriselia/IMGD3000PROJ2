//
// GameStart.cpp
//

// Engine includes.
#include "EventKeyboard.h"
#include "EventStep.h"
#include "GameManager.h"
#include "GraphicsManager.h"	// for COLOR_YELLOW
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"

// Game includes.
#include "GameStart.h"
#include "Hero.h"
#include "Saucer.h"
#include "Trap.h"
#include "MadSquare.h"
#include "Platform.h"
#include "Star.h"

GameStart::GameStart()
{
	setType("GameStart");

	// Link to "message" sprite.
	ResourceManager &resource_manager = ResourceManager::getInstance();
	Sprite *p_temp_sprite = resource_manager.getSprite("gamestart");
	if (!p_temp_sprite)
	{
		LogManager &log_manager = LogManager::getInstance();
		log_manager.writeLog("GameStart::GameStart(): Warning! Sprite 'gamestart' not found");
	}
	else
	{
		setSprite(p_temp_sprite);
		setSpriteSlowdown(15);
	}

	// Put in center of screen.
	setLocation(CENTER_CENTER);

	// Register for "keyboard" event.
	registerInterest(DF_KEYBOARD_EVENT);
}

// Handle event.
// Return 0 if ignored, else 1.
int GameStart::eventHandler(Event *p_e)
{
	GameManager &game_manager = GameManager::getInstance();
	if (isActive())
	{
		if (p_e->getType() == DF_KEYBOARD_EVENT)
		{
			EventKeyboard *p_keyboard_event = (EventKeyboard *)p_e;
			switch (p_keyboard_event->getKey())
			{
			case 'p': 			// play
				start();
				break;
			case 'q':			// quit
				game_manager.setGameOver();
				break;
			default:
				break;
			}
			return 1;
		}
	}


	// If get here, have ignored this event.
	return 0;
}

void GameStart::start()
{

  // Create hero.
  new Hero;
  new Trap;
  new MadSquare;
  new Platform(false, 50, 4, 0, 21, 0.0, 0.1);
  new Platform(true, 30, 6, 17, 11, 0.2, 0.0);
  new Star;
//   ViewObject *p_vo = new ViewObject; // Count of nukes.
//   p_vo->setLocation(TOP_LEFT);
//   p_vo->setViewString("Nukes");
//   p_vo->setValue(1);
//   p_vo->setColor(COLOR_YELLOW);

	// When the game starts, become inactive.
	setActive(false);
}

// Override default draw so as not to display "value".
void GameStart::draw()
{
	Object::draw();
}
