#include "WorldManager.h"
#include "GameManager.h"
#include "LogManager.h"
#include "ExampleObject.h"
#include "EventStep.h"

ExampleObject::ExampleObject()
{
	auto& LogManager = LogManager::getInstance();
	LogManager.writeLog("ExampleObject: Instance Created.\n");
}

ExampleObject::~ExampleObject()
{
	auto& LogManager = LogManager::getInstance();
	LogManager.writeLog("ExampleObject: Instance Destroyed.\n");
}

int ExampleObject::eventHandler(Event *p_event)
{
	auto& gameManager = GameManager::getInstance();
	auto& logManager = LogManager::getInstance();
	auto& worldManager = WorldManager::getInstance();

	if (p_event->getType() == DF_STEP_EVENT)
	{
		auto new_pos = this->getPosition();
		new_pos.setX(new_pos.getX() + 1);
		worldManager.moveObject(this, new_pos);
		logManager.writeLog("ExampleObject: Step Event processed.\n");

		if (new_pos.getX() == 30)
		{
			gameManager.setGameOver();
			logManager.writeLog("ExampleObject: X position reached 30. Requested to end game.\n");
		}
	}

	return 0;
}
