#include "WorldManager.h"
#include "LogManager.h"
#include "GameManager.h"
#include "GraphicsManager.h"
#include "EventStep.h"
#include "EventCollision.h"
#include "EventOut.h"
#include "ViewObject.h"

WorldManager::WorldManager()
{
	deletions = ObjectList();
	updates = ObjectList();
	boundary = Box();
	view = Box();
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

bool boxIntersectsBox(Box A, Box B)
{
	bool x_overlap = false;
	bool y_overlap = false;
	int AL = A.getCorner().getX();
	int AR = A.getCorner().getX() + A.getHorizontal() - 1;
	int BL = B.getCorner().getX();
	int BR = B.getCorner().getX() + B.getHorizontal() - 1;

	x_overlap |= BL <= AL && AL <= BR;
	x_overlap |= BL <= AR && AR <= BR;
	x_overlap |= AL <= BL && BL <= AR;
	x_overlap |= AL <= BR && BR <= AR;

	int AT = A.getCorner().getY();
	int AB = A.getCorner().getY() + A.getVertical() - 1;
	int BT = B.getCorner().getY();
	int BB = B.getCorner().getY() + B.getVertical() - 1;


	y_overlap |= BT <= AT && AT <= BB;
	y_overlap |= BT <= AB && AB <= BB;
	y_overlap |= AT <= BT && BT <= AB;
	y_overlap |= AT <= BB && BB <= AB;
	//y_overlap |= 

	return x_overlap && y_overlap;
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
			if (boxIntersectsBox(getWorldBox(p_o, where), getWorldBox(p_temp_o)) &&
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
bool inBound(Box box)
{
	auto& gfxManager = GraphicsManager::getInstance();
	auto& worldMgr = WorldManager::getInstance();

	int hr = false;
	int x = worldMgr.getBoundary().getVertical();
	int y = worldMgr.getBoundary().getHorizontal();

	Position pos = box.getCorner();


	hr |= pos.getX() > x;
	hr |= pos.getY() > y;
	hr |= (pos.getX() + box.getVertical()) < 0;
	hr |= (pos.getY() + box.getHorizontal()) < 0;

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
				//if (p_o->getOnPlataform() == true || p_temp_o->getOnPlataform() == true)
					//do_move = true;
				itr.next();
			}
			if (!do_move)
			{
				return -1;
			}
		}

	}

	//Check for out of screen event
	if (inBound(getWorldBox(p_o)))
	{
		if (!inBound(getWorldBox(p_o,where)))
		{
			EventOut ov;
			p_o->eventHandler(&ov);
			return 0;
		}
	}

	p_o->setPosition(where);

	if (p_view_following == p_o)
	{
		setViewPosition(p_o->getPosition());
	}
	return 0;
}

void WorldManager::draw()
{
	ObjectListIterator itr(&updates);
	for (int alt = 0; alt <= DF_MAX_ALTITUDE; alt++)
	{
		itr.first();
		while (!itr.isDone())
		{
			if (itr.currentObject()->getAltitude() == alt)
			{
				// Bounding box coordinates are relative to Object,
				// so convert to world coordinates.
				Box temp_box = getWorldBox(itr.currentObject());

				if (boxIntersectsBox(temp_box, view) || // Object in view,
					dynamic_cast <ViewObject*> (itr.currentObject()) || // or is ViewObject.
					((itr.currentObject()->getType()) == "Star"))
				{
					itr.currentObject()->draw();

				}
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
			itr.currentObject()->FloorVelocityCountdown();
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
	auto& gfxManager = GraphicsManager::getInstance();

	int x = gfxManager.getVertical();
	int y = gfxManager.getHorizontal();

	boundary = Box(Position(), x * 2, y * 2);
	view = Box(Position(), x, y);
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

void WorldManager::setViewPosition(Position view_pos)
{
	// Make sure horizontal not out of world boundary.
	int x = view_pos.getX() - view.getHorizontal() / 2;
	if ((x + view.getHorizontal()) > boundary.getHorizontal())
	{
		x = boundary.getHorizontal() - view.getHorizontal();

	}
	if (x < 0)
	{
		x = 0;
	}
	// Make sure vertical not out of world boundary.
	int y = view_pos.getY() - view.getVertical() / 2;
	if ((y + view.getVertical()) > boundary.getVertical())
	{
		y = boundary.getVertical() - view.getVertical();
	}
	if (y < 0)
	{
		y = 0;
	}
	// Set view.
	Position new_corner(x, y);
	view.setCorner(new_corner);
}

int WorldManager::setViewFollowing(Object *p_new_view_following)
{
	if (!p_new_view_following)
	{
		this->p_view_following = nullptr;
		return 0;
	}

	auto itr = ObjectListIterator(&updates);
	for (itr.first(); !itr.isDone(); itr.next())
	{
		if (itr.currentObject() == p_new_view_following)
		{
			p_view_following = p_new_view_following;
			setViewPosition(p_view_following->getPosition());
		}
	}
}