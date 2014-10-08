//
// game.cpp
// 

// Engine includes.
#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"

// Game includes.
#include "Hero.h"
#include "Star.h"
#include "Saucer.h"
#include "ViewObject.h"

// Function prototypes.
void populateWorld(void);
void loadResources();

int main(int argc, char *argv[])
{
	LogManager &log_manager = LogManager::getInstance();

	// Start up game manager.
	GameManager &game_manager = GameManager::getInstance();
	if (game_manager.startUp())
	{
		log_manager.writeLog("Error starting game manager!");
		game_manager.shutDown();
		return 0;
	}

	// Load game resources.
	loadResources();

	// Set flush of logfile during development (when done, make false).
	log_manager.setFlush(true);

	// Setup some objects.
	populateWorld();

	// Run game (this blocks until game loop is over).
	game_manager.run();

	// Shut everything down.
	game_manager.shutDown();
}

void loadResources()
{
	int hr = 0;
	ResourceManager &resource_manager = ResourceManager::getInstance();
	auto& gameMgr = GameManager::getInstance();

	hr |= resource_manager.loadSprite("sprites/ship-spr.txt", "hero");
	hr |= resource_manager.loadSprite("sprites/saucer-spr.txt", "saucer");
	hr |= resource_manager.loadSprite("sprites/bullet-spr.txt", "bullet");
	hr |= resource_manager.loadSprite("sprites/explosion-spr.txt", "explosion");

	if (hr)
	{
		auto& logger = LogManager::getInstance();
		logger.writeLog("Resource loading failed.\n");
		gameMgr.shutDown();
		exit(-1);
	}
}

// Populate world with some objects.
void populateWorld(void)
{

	// Spawn some Stars.
	for (int i = 0; i <108; i++)
	{
		new Star;
	}

	// Create hero.
	new Hero;
	auto a = new ViewObject;
	a->setLocation(TOP_CENTER);
	a->setViewString("Score");
	a->setValue(0);

	// Spawn some saucers to shoot.
	for (int i = 0; i < 16; i++)
	{
		//new Saucer;
	}
	return;
}
