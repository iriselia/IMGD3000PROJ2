#include "WorldManager.h"
#include "LogManager.h"

WorldManager::WorldManager()
{

}

ObjectList WorldManager::objectsInCircle(Circle circle) const
{
	return deletions;
}

ObjectList WorldManager::objectsOnLine(Line line) const
{
	return deletions;
}

ObjectList WorldManager::objectsInBox(Box box) const
{
	return deletions;
}

ObjectList WorldManager::objectsAtPosition(Position where) const
{
	return deletions;
}

Object * WorldManager::objectWithId(int id) const
{
	return nullptr;
}

ObjectList WorldManager::isCollision(Object *p_o, Position where) const
{
	return deletions;
}

int WorldManager::moveObject(Object *p_o, Position where)
{
	p_o->setPosition(where);
	return 0;
}

void WorldManager::draw()
{

}

void WorldManager::update()
{
	auto& logManager = LogManager::getInstance();
	// Deferred object removal
	auto deletionLi = ObjectListIterator(&deletions);
	for (deletionLi.first(); !deletionLi.isDone(); deletionLi.next())
	{
		delete deletionLi.currentObject();
		deletions.remove(deletionLi.currentObject());
	}

	logManager.writeLog("WorldManager: Deferred object removal successful.\n");
}

int WorldManager::markForDelete(Object *p_o)
{
	this->deletions.insert(p_o);
	return 0;
}

ObjectList WorldManager::getAllObjects(void) const
{
	return this->updates;
}

int WorldManager::removeObject(Object *p_o)
{
	this->updates.remove(p_o);
	return 0;
}

int WorldManager::insertObject(Object *p_o)
{
	this->updates.insert(p_o);
	return 0;
}

void WorldManager::shutDown()
{
	if (this->isStarted())
	{
		updates.clear();
		deletions.clear();
		//shutdown base at the end
		Manager::shutDown();
	}

	auto& logManager = LogManager::getInstance();
	logManager.writeLog("WorldManager: Shutting down.\n");
}

int WorldManager::startUp()
{
	auto& logManager = LogManager::getInstance();

	//start up base first
	bool b_isFailed = Manager::startUp();

	logManager.writeLog("WorldManager: Initialized.\n");
	return 0;
}

bool WorldManager::isValid(string event_type) const
{
	if (event_type == "")
	{
		return true;
	}
	else
	{
		return false;
	}
}

