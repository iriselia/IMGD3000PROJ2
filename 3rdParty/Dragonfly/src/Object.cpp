#include "Object.h"
#include "WorldManager.h"
#include "GraphicsManager.h"

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
	auto& gfxMgr = GraphicsManager::getInstance();
	int index = getSpriteIndex();
	int count = getSpriteSlowdownCount();
	gfxMgr.drawFrame(pos, p_sprite->getFrame(index), isCentered(), this->sprite_transparency, p_sprite->getColor());

	if (sprite_slowdown == 0)
	{
		return;
	}
	else
	{
		count++;
		if (count >= sprite_slowdown)
		{
			count = 0;
			++index %= (p_sprite->getFrameCount());
		}
	}

	setSpriteSlowdownCount(count);
	setSpriteIndex(index);
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
	pos = Position(0, 0);               ///< Position in the game world.
	x_velocity = 0;           ///< Horizontal speed in spaces per game step.
	x_velocity_countdown = 0; ///< Countdown to horizontal movement.
	y_velocity = 0;           ///< Vertical speed in spaces per game step.
	y_velocity_countdown = 0; ///< Countdown to vertical movement.
	altitude = 0;
	sprite_index = 0;
	sprite_slowdown = 0;
	sprite_slowdown_count = 0;
	sprite_center = false;
	solidness = HARD;
	sprite_center = true;
	p_sprite = nullptr;
	onPlatform = false;
	auto & worldManager = WorldManager::getInstance();
	worldManager.insertObject(this);
}

Object::~Object()
{
	auto & worldManager = WorldManager::getInstance();
	worldManager.removeObject(this);
}
