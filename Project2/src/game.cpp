//
// game.cpp
// 

// Engine includes.
#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"

// Game includes.
#include "GameStart.h"
#include "ViewObject.h"
#include "Platform.h"

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

	auto& worldManager = WorldManager::getInstance();
	worldManager.setBoundary(Box(Position(0, 0), 2000, 80));

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

	//hero sprites
	hr |= resource_manager.loadSprite("sprites/hero/hero-walk-left-spr.txt", "hero_walk_left");
	hr |= resource_manager.loadSprite("sprites/hero/hero-walk-right-spr.txt", "hero_walk_right");
	hr |= resource_manager.loadSprite("sprites/hero/hero-jump-spr.txt", "hero_jump");

	//monster sprites
	hr |= resource_manager.loadSprite("sprites/madsquare-spr.txt", "madsquare");
	hr |= resource_manager.loadSprite("sprites/suicider-spr.txt", "suicider");

	//bullets
	hr |= resource_manager.loadSprite("sprites/bullet-right-spr.txt", "bullet-right");
	hr |= resource_manager.loadSprite("sprites/bullet-left-spr.txt", "bullet-left");
	hr |= resource_manager.loadSprite("sprites/bullet1-spr.txt", "bullet1");

	//effects
	hr |= resource_manager.loadSprite("sprites/explosion-spr.txt", "explosion");
	hr |= resource_manager.loadSprite("sprites/trap-spr.txt", "trap");
	
	//game related
	hr |= resource_manager.loadSprite("sprites/gamestart-spr.txt", "gamestart");
	hr |= resource_manager.loadSprite("sprites/gameover-spr.txt", "gameover");
	hr |= resource_manager.loadSprite("sprites/gameoverflag-spr.txt", "gameoverflag");
	hr |= resource_manager.loadSprite("sprites/gamewin-spr.txt", "gamewin");
	hr |= resource_manager.loadSprite("sprites/winflag-spr.txt", "winflag");



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
	new GameStart;
	return;
}
