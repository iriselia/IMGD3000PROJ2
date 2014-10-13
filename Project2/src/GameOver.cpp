//
// GameOver.cpp
//

// Engine includes.
#include "EventStep.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"

// Game includes.
#include "GameOver.h"
//#include "GameStart.h"

GameOver::GameOver()
{

	setType("GameOver");

	// Link to "message" sprite.
	ResourceManager &resource_manager = ResourceManager::getInstance();
	Sprite *p_temp_sprite = resource_manager.getSprite("gameover");
	if (!p_temp_sprite)
	{
		LogManager &log_manager = LogManager::getInstance();
		log_manager.writeLog("GameOver::GameOver(): Warning! Sprite 'gameover' not found");
	}
	else
	{
		setSprite(p_temp_sprite);
		setSpriteSlowdown(15);
		setTransparency('#');    // Transparent character.
		time_to_live = p_temp_sprite->getFrameCount() * 15;
	}

	// Put in center of screen.
	setLocation(CENTER_CENTER);
	setPosition(viewToWorld(getPosition()));

	// Register for step event.
	registerInterest(DF_STEP_EVENT);
}

// When done, game over.
GameOver::~GameOver()
{
	WorldManager &world_manager = WorldManager::getInstance();

	// Remove Saucers and ViewObjects, re-activate GameStart.
	ObjectList object_list = world_manager.getAllObjects();
	ObjectListIterator i(&object_list);
	for (i.first(); !i.isDone(); i.next())
	{
		Object *p_o = i.currentObject();
		if (p_o->getType() == "Saucer" || p_o->getType() == "ViewObject")
			world_manager.markForDelete(p_o);
		if (p_o->getType() == "GameStart")
			p_o->setActive(true);
	}
}

// Handle event.
// Return 0 if ignored, else 1.
int GameOver::eventHandler(Event *p_e)
{

	if (p_e->getType() == DF_STEP_EVENT)
	{
		step();
		return 1;
	}

	// If get here, have ignored this event.
	return 0;
}

// Count down to end of message.
void GameOver::step()
{

	time_to_live--;
	if (time_to_live <= 0)
	{
		WorldManager &world_manager = WorldManager::getInstance();
		world_manager.markForDelete(this);
	}
}

// Override default draw so as not to display "value".
void GameOver::draw()
{
	Object::draw();
}
