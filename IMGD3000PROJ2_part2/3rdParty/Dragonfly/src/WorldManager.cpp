#include "WorldManager.h"
#include "LogManager.h"
#include "GameManager.h"
#include "GraphicsManager.h"
#include "EventStep.h"
#include "EventCollision.h"
#include "EventOut.h"

WorldManager::WorldManager()
{
	deletions = ObjectList();
	updates = ObjectList();
	boundary = Box();
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


///*
// Return true if two positions intersect, else false.
bool positionsIntersect(Position p1, Position p2)
{
	if ((p1.getX() == p2.getX()) &&
		(p1.getY() == p2.getY()))
	{
		return true;
	}
	else
	{
		return false;
	}
}

//*/

ObjectList WorldManager::isCollision(Object *p_o, Position where) const
{
	// Make empty list.
	ObjectList collision_list;
		// Iterate through all objects.
	auto itr = ObjectListIterator(&updates);
	itr.first();
	while (!itr.isDone())
	{
		Object *p_temp_o = itr.currentObject();
		if (p_temp_o != p_o)// Do not consider self.
		{
			// Same location and both solid?
			if (positionsIntersect(p_temp_o->getPosition(), where) &&
				p_temp_o->isSolid())
			{
				collision_list.insert(p_temp_o);
			}
		}
			itr.next();
	}


	return collision_list;
}

///*
// Return true if two positions intersect, else false.
bool inBound(Position pos)
{
	auto& gfxManager = GraphicsManager::getInstance();

	int hr = false;
	int x = gfxManager.getVertical();
	int y = gfxManager.getHorizontal();

	hr |= pos.getX() > x;
	hr |= pos.getY() > y;
	hr |= pos.getX() < 0;
	hr |= pos.getY() < 0;

	return hr ? false : true;
}

//*/

int WorldManager::moveObject(Object *p_o, Position where)
{

	if (p_o->isSolid())// Need to be solid for collisions.
	{
		// Get collisions.
		ObjectList list = isCollision(p_o, where);
		if (!list.isEmpty())
		{
			// Iterate over list.
			auto itr = ObjectListIterator(&list);
			itr.first();
			bool do_move = true;
			while (!itr.isDone())
			{
				Object *p_temp_o = itr.currentObject();
				// Create collision event.
				EventCollision c(p_o, p_temp_o, where);
					// Send to both objects.
				p_o->eventHandler(&c);
				p_temp_o->eventHandler(&c);
				// If both HARD, then cannot move.
				if ((p_o->getSolidness() == HARD) && (p_temp_o->getSolidness() == HARD))
				{
					do_move = false;
				}
				itr.next();
			}
			if (!do_move)
			{
				return -1;
			}
		}

	}

	//Check for out of screen event
	if (inBound(p_o->getPosition()))
	{
		if (!inBound(where))
		{
			EventOut ov;
			p_o->eventHandler(&ov);
			return 0;
		}
	}

	p_o->setPosition(where);
	return 0;
}

void WorldManager::draw()
{
	ObjectListIterator itr(&updates);
	for (int alt = 0; alt < DF_MAX_ALTITUDE; alt++)
	{
		itr.first();
		while (!itr.isDone())
		{
			if (itr.currentObject()->getAltitude() == alt)
			{
				itr.currentObject()->draw();
			}
			itr.next();
		}
	}

}

void WorldManager::update()
{
	auto& logManager = LogManager::getInstance();
	auto& gameManager = GameManager::getInstance();
	auto& gfxManager = GraphicsManager::getInstance();

	// Update all objects
	auto stepEvent = EventStep(gameManager.getStepCount());
	onEvent(&stepEvent);
	logManager.writeLog("GameManager: Step Event sent to all objects.\n");

	// Move all objects
	auto itr = ObjectListIterator(&updates);
	itr.first();
	while (!itr.isDone())
	{
		int x = itr.currentObject()->getXVelocityStep();
		int y = itr.currentObject()->getYVelocityStep();

		if (x || y)
		{
			auto oldPos = itr.currentObject()->getPosition();
			auto newPos = Position(oldPos.getX() + x, oldPos.getY() + y);
			moveObject(itr.currentObject(), newPos);
		}
		itr.next();
	}

	// Deferred object removal
	deletions.clear();
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

