// Engine includes
//#include <vld.h>
#include "GameManager.h"
#include "LogManager.h"
#include "WorldManager.h"
#include <direct.h>

#include "ExampleObject.h"

int main(int argc, char *argv[])
{
	LogManager &log_manager = LogManager::getInstance();
	// Start up Game Manager.
	GameManager &game_manager = GameManager::getInstance();
	if (game_manager.startUp())
	{
		log_manager.writeLog("Error starting game manager!");
		game_manager.shutDown();
		return 0;
	}

	// Set flush of logfile during development (when done, make false).
	log_manager.setFlush(true);

 	auto a = new ExampleObject();
 	auto& worldManager = WorldManager::getInstance();

	auto b = new ExampleObject();
 	worldManager.markForDelete(a);
 	log_manager.writeLog("Main: Second ExampleObject marked for delete.\n");
	// Run game (this blocks until game loop is over).
	game_manager.run();

	// Shut everything down.
	game_manager.shutDown();
	return 0;
}
