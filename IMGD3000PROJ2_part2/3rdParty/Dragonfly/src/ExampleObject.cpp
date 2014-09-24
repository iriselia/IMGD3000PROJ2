#include "WorldManager.h"
#include "GameManager.h"
#include "LogManager.h"
#include "ExampleObject.h"
#include "EventStep.h"
#include "EventOut.h"
#include "EventKeyboard.h"
#include "GraphicsManager.h"

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
		logManager.writeLog("ExampleObject: Step Event processed.\n");

		if (getPosition().getX() == 30)
		{
			//gameManager.setGameOver();
			logManager.writeLog("ExampleObject: X position reached 30. Requested to end game.\n");
		}
	}
	else if (p_event->getType() == DF_OUT_EVENT)
	{
		logManager.writeLog("ExampleObject: Out Event processed.\n");
		setPosition(Position(40, getPosition().getY()));
	}
	else if (p_event->getType() == DF_KEYBOARD_EVENT)
	{
		logManager.writeLog("ExampleObject: Keyboard Event processed.\n");
		EventKeyboard *p_keyboard_event = static_cast <EventKeyboard *> (p_event);
		switch (p_keyboard_event->getKey())
		{
		case KEY_RIGHT:		// up arrow
			setXVelocity(abs(getXVelocity()));
			break;
		case KEY_LEFT:		// down arrow
			setXVelocity(-abs(getXVelocity()));
			break;
		};
		return 1;
	}

	return 0;
}
