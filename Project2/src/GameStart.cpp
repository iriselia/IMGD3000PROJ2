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
#include "Suicider.h"
#include "Star.h"
#include "WinFlag.h"

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
	new Star;

	// Area 1
	
							//x y
	new Platform(false, 100, 6, 0, 11+15, 0.0, 0.0); // size, height, x, y, xspeed, yspeed
	new Platform(true, 30, 6, 105, 12+15, 0.0, 0.0);
	new Trap(106, 26);
	new Trap(126, 26);

	new Platform(true, 40, 6, 150, 30+15, 0.0, 0.6); // size, height, x, y, xspeed, yspeed
	new Platform(false, 60, 6, 200, 20+15, 0.2, 0.0); // size, height, x, y, xspeed, yspeed
	new Trap(210, 34);
	new Platform(false, 20, 6, 240, 14+15, 0.0, 0.0); // size, height, x, y, xspeed, yspeed
	new Trap(250, 28);
	new Platform(true, 40, 10, 250, 0+15, 0.0, 0.0); // size, height, x, y, xspeed, yspeed
	new Platform(false, 50, 6, 300, 30, 0.0, 0.0); // size, height, x, y, xspeed, yspeed
	new Trap(301, 29);
	new Platform(true, 106, 6, 353, 39, 0.3, 0.0); // size, height, x, y, xspeed, yspeed
	new MadSquare(360, 29);

	// Area 2
	//new Platform(false, 200, 6, 450, 45, 0.0, 0.0); // size, height, x, y, xspeed, yspeed
	
	new Platform(false, 80, 10, 460, 45, 0.0, 0.0); // size, height, x, y, xspeed, yspeed
	new Trap(465, 44);
	new MadSquare(500, 12);
	new Platform(true, 30, 20, 440, 10, 0.0, 0.0); // size, height, x, y, xspeed, yspeed
	new Platform(true, 30, 30, 490, 15, 0.0, 0.0); // enemy after this // dogs // yellow

	
	new Platform(false, 35, 10, 550, 45, 0.2, 0.0); // size, height, x, y, xspeed, yspeed
	new Suicider(550, 43);
	new Platform(true, 200, 5, 590, 48, 0.0, 0.0); // enemies here
	new Platform(false, 50, 6, 780, 55, 0.0, 0.3); // size, height, x, y, xspeed, yspeed
	new Platform(true, 126, 6, 835, 70, 0.0, 0.0); // size, height, x, y, xspeed, yspeed
	new Platform(true, 250, 20, 920, 50, 0.0, 0.0); // size, height, x, y, xspeed, yspeed
	new MadSquare(1000, 40);
	//Area 3
	new Platform(false, 110, 10, 1180, 55, 0.3, 0.0); // down
	new Suicider(1290, 52);
	new Platform(true, 75, 5, 1173, 45, 0.0, 0.15); // up
	new Platform(true, 30, 4, 1222, 33, 0.0, 0.0); // up
	new MadSquare(1230, 29);
	new Platform(true, 30, 4, 1260, 33, 0.0, 0.0); // up
	new Platform(true, 30, 4, 1299, 33, 0.0, 0.0); // up
	new Platform(false, 110, 30, 1295, 50, 0.0, 0.0); // down
	new Platform(false, 90, 5, 1409, 45, 0.0, 0.0); // down
	new Platform(false, 20, 5, 1509, 39, 0.4, 0.0); // down
	new Platform(false, 50, 7, 1531, 33, 0.0, 0.0); // down

	//new Platform(false, 35, 10, 550, 45, 0.2, 0.0); // size, height, x, y, xspeed, yspeed
	//new Platform(true, 200, 5, 590, 48, 0.0, 0.0); // enemies here
	//new Platform(false, 50, 6, 780, 55, 0.0, 0.3); // size, height, x, y, xspeed, yspeed
	//new Platform(true, 126, 6, 835, 70, 0.0, 0.0); // size, height, x, y, xspeed, yspeed
	//new Platform(true, 250, 20, 920, 50, 0.0, 0.0); // size, height, x, y, xspeed, yspeed

	// Create hero.
	//new Trap(35, 6);
	//new MadSquare(45, 7);



	new WinFlag(1545, 31);
	new Hero(1380, 10);
	//new Hero(380, 10);

	//new WinFlag(40, 20);
	
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
