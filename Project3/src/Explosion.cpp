//
// Explosion.cpp
//

// Engine includes.
#include "EventStep.h"
#include "GameManager.h"
#include "GraphicsManager.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"

// Game includes.
#include "Explosion.h"

Explosion::Explosion()
{
	setType("Explosion");

	// Exit after about 6 steps.
	time_to_live = 6;

	// Doesn't collide
	setSolidness(SPECTRAL);

	auto& resMgr = ResourceManager::getInstance();

	setSprite(resMgr.getSprite("explosion"));
	setSpriteSlowdown(4);

#ifdef REGISTER
	// Need step event to countdown.
	registerInterest(DF_STEP_EVENT);
#endif

}

// Handle event.
// Return 0 if ignored, else 1.
int Explosion::eventHandler(Event *p_e)
{

	if (p_e->getType() == DF_STEP_EVENT)
	{
		step();
		return 1;
	}

	// If get here, have ignored this event.
	return 0;
}

// Count down until explosion finished.
void Explosion::step()
{
	time_to_live--;
	if (time_to_live <= 0)
	{
		WorldManager &world_manager = WorldManager::getInstance();
		world_manager.markForDelete(this);
	}
}

void Explosion::draw()
{
	Object::draw();
}
