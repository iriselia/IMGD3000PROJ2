// Engine includes
#include "GameManager.h"
#include "LogManager.h"

int main(int argc, char *argv[]) {
	LogManager &log_manager = LogManager::getInstance();

	// Start up Game Manager.
	GameManager &game_manager = GameManager::getInstance();
	if (game_manager.startUp())  {
		log_manager.writeLog("Error starting game manager!");
		game_manager.shutDown();
		return 0;
	}

	// Set flush of logfile during development (when done, make false).
	log_manager.setFlush(true);

	// Shut everything down.
	game_manager.shutDown();
}
