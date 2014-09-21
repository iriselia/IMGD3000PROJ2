#include "GameManager.h"
#include "WorldManager.h"
#include "LogManager.h"
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
	srand(seed);

	return b_isFailed;
}

void GameManager::shutDown()
{
	if (this->isStarted())
	{
		auto& logManager = LogManager::getInstance();
		logManager.writeLog("GameManager: Shutting down.\n");

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

	while (!game_over)
	{
		this->step_count++;
		clock.delta();
		// Get input (e.g., keyboard/mouse)

		// Update world state
		auto list = worldManager.getAllObjects();

		EventStep event;
		event.setStepCount(step_count);
		auto li = ObjectListIterator(&list);
		for (li.first(); !li.isDone(); li.next())
		{
			if (li.currentObject() != nullptr)
			{
				li.currentObject()->eventHandler(&event);
			}
		}
		logManager.writeLog("GameManager: Step Event sent to all objects.\n");
		worldManager.update();

		// Draw new scene to back buffer
		// Swap back buffer to current buffer
		auto sleepTime = frame_time - clock.split();
		if (sleepTime > 0)
		{
			Sleep(sleepTime);
		}
	}
}
