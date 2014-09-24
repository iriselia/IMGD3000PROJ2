#include "Manager.h"
#include "WorldManager.h"

/// Check if event is handled by this Manager.
/// If handled, return true else false.
/// (Base Manager always returns false.)
bool Manager::isValid(string event_type) const
{
	return false;
}

	 /// Set type identifier of Manager.
void Manager::setType(string type)
{
	this->type = type;
}

Manager::Manager()
{

}

Manager::~Manager()
{

}

	 /// Get type identifier of Manager.
string Manager::getType() const
{
	return this->type;
}

//TODO: ask claypool about this
	 /// Startup Manager. 
	 /// Return 0 if ok, else negative number.
int Manager::startUp()
{
	is_started = true;
	return 0;
}

	 /// Shutdown Manager.  
void Manager::shutDown()
{
	is_started = false;
}

	 /// Return status of is_started (true when startUp() was successful).
bool Manager::isStarted() const
{
	return is_started;
}
	 /// Send event to all interested objects.
	 /// Return count of number of events sent.
int Manager::onEvent(Event *p_event) const
{
	auto objects = WorldManager::getInstance().getAllObjects();
	auto itr = ObjectListIterator(&objects);
	itr.first();
	int count = 0;
	while (!itr.isDone())
	{
		itr.currentObject()->eventHandler(p_event);
		itr.next();
		count++;
	}

	return count;
}
//todo
	 /// Indicate interest in event.
	 /// Return 0 if ok, else -1.
	 /// (Note, doesn't check to see if Object is already registered.)
int Manager::registerInterest(Object *p_o, string event_type)
{
	//this->obj_list->insert(p_o);
	return 0;
}
//todo
	 /// Indicate no more interest in event. 
	 /// Return 0 if ok, else -1.
int Manager::unregisterInterest(Object *p_o, string event_type)
{
	return 0;
}