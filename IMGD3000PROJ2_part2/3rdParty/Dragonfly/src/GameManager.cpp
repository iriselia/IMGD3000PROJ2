#include "GameManager.h"
#include "WorldManager.h"
#include "LogManager.h"
#include "GraphicsManager.h"
#include "InputManager.h"
#include "Clock.h"
#include "EventStep.h"

GameManager::GameManager()
{

}

bool GameManager::isValid(string event_name) const
{
	return event_name == DF_STEP_EVENT;
}

int GameManager::startUp(time_t seed /*= 0*/)
{
	//start up base first
	bool b_isFailed = Manager::startUp();

	LogManager::getInstance().startUp();
	WorldManager::getInstance().startUp();
	GraphicsManager::getInstance().startUp();
	InputManager::getInstance().startUp();
	srand(seed);

	return b_isFailed;
}

void GameManager::shutDown()
{
	if (this->isStarted())
	{
		auto& logManager = LogManager::getInstance();
		logManager.writeLog("GameManager: Shutting down.\n");

		InputManager::getInstance().shutDown();
		GraphicsManager::getInstance().shutDown();
		WorldManager::getInstance().shutDown();
		LogManager::getInstance().shutDown();

		//shutdown base at the end
		Manager::shutDown();
	}
}

void GameManager::run(int frame_time /*= DF_DEFAULT_FRAME_TIME*/)
{
	Clock clock;
	auto& worldManager = WorldManager::getInstance();
	auto& logManager = LogManager::getInstance();
	auto& gfxManager = GraphicsManager::getInstance();
	auto& inputManager = InputManager::getInstance();

	while (!game_over)
	{
		this->step_count++;
		clock.delta();
		// Get input (e.g., keyboard/mouse)
		inputManager.getInput();
		// Update world state
		worldManager.update();
		// Draw new scene to back buffer
		worldManager.draw();
		gfxManager.swapBuffers();
		// Swap back buffer to current buffer
		auto sleepTime = frame_time - clock.split();
		if (sleepTime > 0)
		{
			Sleep(sleepTime);
		}
	}
}
