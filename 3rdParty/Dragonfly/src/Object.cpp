#include "Object.h"
#include "WorldManager.h"

bool Object::isModified() const
{
	return false;
}

bool Object::isModified(enum ObjectAttribute attribute) const
{
	return false;
}

int Object::deserialize(string s)
{
	return 0;
}

string Object::serialize(bool all /*= false*/)
{
	if (!all)
	{
		//ObjectAttribute;
	}
	return "";
}

void Object::draw()
{

}

int Object::unregisterInterest(string event_type)
{
	return 0;
}

int Object::registerInterest(string event_type)
{
	return 0;
}

int Object::eventHandler(Event *p_event)
{
	return 0;
}

Object::Object()
{
	auto & worldManager = WorldManager::getInstance();
	worldManager.insertObject(this);
}

Object::~Object()
{
	auto & worldManager = WorldManager::getInstance();
	worldManager.removeObject(this);
}
