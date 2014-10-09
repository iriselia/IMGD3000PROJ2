//
// Saucer.cpp
//

#include <stdlib.h>		// for random()

// Engine includes.
#include "EventCollision.h"
#include "EventNuke.h"
#include "EventOut.h"
#include "GraphicsManager.h"
#include "LogManager.h"
#include "WorldManager.h"

#include "ResourceManager.h"

// Game includes.
#include "Explosion.h"
#include "Platform.h"
#include "EventView.h"


Platform::Platform()
{
	setType("Platform");
	isItThick = false;
	size = 50;
	setSolidness(HARD);
	setXVelocity(0.0);
	setYVelocity(0.0);
	setAltitude(2);	// Make them in the background.
	WorldManager &world_manager = WorldManager::getInstance();
	//Position pos(random() % world_manager.getBoundary().getHorizontal(),
	//	random() % world_manager.getBoundary().getVertical());
	Position pos(0, 15);
	setPosition(pos);
	height = 5;
	setBox(Box(Position(), size, height));




}

Platform::Platform(bool thickness, int sizee, int heightt, int x, int y)
{
	setType("Platform");
	isItThick = thickness;
	size = sizee;
	setSolidness(HARD);
	setXVelocity(0.0);
	move_countdown = 50;
	setYVelocity(0.02);
	setAltitude(0);	// Make them in the background.
	WorldManager &world_manager = WorldManager::getInstance();
	//Position pos(random() % world_manager.getBoundary().getHorizontal(),
	//	random() % world_manager.getBoundary().getVertical());
	Position pos(x, y);
	setPosition(pos);
	height = heightt;
	setBox(Box(Position(), size, height));




}
// Handle event.
// Return 0 if ignored, else 1.
int Platform::eventHandler(Event *p_e)
{

	if (p_e->getType() == DF_OUT_EVENT)
	{
		out();
		return 1;
	}

	if (p_e->getType() == DF_COLLISION_EVENT)
	{
		EventCollision *p_collision_event = static_cast <EventCollision *> (p_e);
		//hit(p_collision_event);
		return 1;
	}

	if (p_e->getType() == NUKE_EVENT)
	{

		// Create explosion.
		//Explosion *p_explosion = new Explosion;
		//p_explosion->setPosition(this->getPosition());

		// Delete self.
		//WorldManager &world_manager = WorldManager::getInstance();
		//world_manager.markForDelete(this);

		// Platforms appear stay around perpetually
		//new Platform;
	}

	if (p_e->getType() == DF_STEP_EVENT)
	{
		EventStep *p_step_event = static_cast <EventStep *> (p_e);
		step(p_step_event);
	}
	// If get here, have ignored this event.
	return 0;
}

void Platform::step(EventStep *p_s)
{
	// move left and right

	if (move_countdown < 0)
	{

		setXVelocity(getXVelocity() * -1);
		move_countdown = 100;
	}
}

// If moved off left edge, move back to far right.
void Platform::out()
{

	// If haven't moved off left edge, then nothing to do.
	if (getPosition().getX() >= 0)
		return;

	// Otherwise, move back to far right.
	//moveToStart();

	// Spawn new Saucer to make the game get harder.
	new Platform;

}

// If saucer and player collide, mark both for deletion.
/*
void Platform::hit(EventCollision *p_c)
{

	// If Saucer on Saucer, ignore.
	if ((p_c->getObject1()->getType() == "Platform") &&
		(p_c->getObject2()->getType() == "Platform"))
		return;

	// If Bullet ...
	if ((p_c->getObject1()->getType() == "Bullet") ||
		(p_c->getObject2()->getType() == "Bullet"))
	{

		// Create an explosion.
		Explosion *p_explosion = new Explosion;
		p_explosion->setPosition(this->getPosition());

		auto& worldMgr = WorldManager::getInstance();
		EventView ev;
		ev.setDelta(true);
		ev.setValue(10);
		ev.setTag("Score");
		worldMgr.onEvent(&ev);
		// Saucers appear stay around perpetually.
		new Platform;
	}

	// If Hero, mark both objects for destruction.
	if (((p_c->getObject1()->getType()) == "Hero") ||
		((p_c->getObject2()->getType()) == "Hero"))
	{
		WorldManager &world_manager = WorldManager::getInstance();
		world_manager.markForDelete(p_c->getObject1());
		world_manager.markForDelete(p_c->getObject2());
	}

}

*/


// Move saucer to starting location on right side of screen.
/*
void Platform::moveToStart()
{
	WorldManager &world_manager = WorldManager::getInstance();
	Position temp_pos;

	// Get world boundaries.
	int world_horiz = world_manager.getBoundary().getHorizontal() / 2;
	int world_vert = world_manager.getBoundary().getVertical();

	// x is off right side of screen.
	temp_pos.setX(world_horiz + random() % world_horiz + 3);

	// y is in vertical range.
	temp_pos.setY(random() % (world_vert - 4) + 4);

	// If collision, move right slightly until empty space.
	ObjectList collision_list = world_manager.isCollision(this, temp_pos);
	while (!collision_list.isEmpty())
	{
		temp_pos.setX(temp_pos.getX() + 1);
		temp_pos.setY(temp_pos.getX() + 1);
		collision_list = world_manager.isCollision(this, temp_pos);
	}

	world_manager.moveObject(this, temp_pos);
	//world_manager.moveObject(this, Position(40, 2));
}

*/

void Platform::draw()
{
	//Object::draw();

	GraphicsManager &graphics_manager = GraphicsManager::getInstance();

	if (isItThick == false)
	{
		if (height <= 2)
		{

			for (int i = 0; i < size; i++)
			{
				Position temp(getPosition().getX() + i, getPosition().getY());

				graphics_manager.drawCh(temp, PLATFORM_THIN);
			}


		}
		else
		{
			for (int j = 0; j < height; j++)
			{
				if (j == 0 || j == (height - 1))
				{
					for (int i = 0; i < size; i++)
					{
						Position temp(getPosition().getX() + i, getPosition().getY());

						graphics_manager.drawCh(temp, PLATFORM_THIN);
						//graphics_manager.drawCh(temp, PLATFORM_THIN_WALL);
					}

				}
				else
				{
					Position temp(getPosition().getX(), getPosition().getY()+j);

					graphics_manager.drawCh(temp, PLATFORM_THIN_WALL);
					temp.setXY(getPosition().getX() + size -1, getPosition().getY()+j);
					graphics_manager.drawCh(temp, PLATFORM_THIN_WALL);

				}
				


			} // end j for
			
			for (int i = 0; i < size; i++)
			{
				if (i <= size - 3)
				{
					Position temp(getPosition().getX() + i + 1, getPosition().getY() + height - 2);
					graphics_manager.drawCh(temp, PLATFORM_THIN);
				}
				else
				{
					Position temp(getPosition().getX() + i  , getPosition().getY() + height - 2);
					//graphics_manager.drawCh(temp, PLATFORM_THIN);
				}
				

				//graphics_manager.drawCh(temp, PLATFORM_THIN);
				//graphics_manager.drawCh(temp, PLATFORM_THIN_WALL);
			}
		} // end else

	}
	else
	{

		if (height <= 2)
		{

			for (int i = 0; i < size; i++)
			{
				Position temp(getPosition().getX() + i, getPosition().getY());

				graphics_manager.drawCh(temp, PLATFORM_THICK);
			}


		}
		else
		{
			for (int j = 0; j < height; j++)
			{
				if (j == 0 || j == (height - 1))
				{
					for (int i = 0; i < size; i++)
					{
						Position temp(getPosition().getX() + i, getPosition().getY());

						graphics_manager.drawCh(temp, PLATFORM_THICK);
						//graphics_manager.drawCh(temp, PLATFORM_THIN_WALL);
					}

				}
				else
				{
					Position temp(getPosition().getX(), getPosition().getY() + j);

					graphics_manager.drawCh(temp, PLATFORM_THICK_WALL);
					temp.setXY(getPosition().getX() + size - 1, getPosition().getY() + j);
					graphics_manager.drawCh(temp, PLATFORM_THICK_WALL);

				}



			} // end j for

			for (int i = 0; i < size; i++)
			{
				if (i <= size - 3)
				{
					Position temp(getPosition().getX() + i + 1, getPosition().getY() + height - 2);
					graphics_manager.drawCh(temp, PLATFORM_THICK);
				}
				else
				{
					Position temp(getPosition().getX() + i, getPosition().getY() + height - 2);
					//graphics_manager.drawCh(temp, PLATFORM_THIN);
				}


				//graphics_manager.drawCh(temp, PLATFORM_THIN);
				//graphics_manager.drawCh(temp, PLATFORM_THIN_WALL);
			}
		} // end else


	}

	//  	GraphicsManager &graphics_manager = GraphicsManager::getInstance();
	// 	Box box = getBox();
	// 	std::stringstream curPos;
	// 	curPos << "Saus Position: " << getPosition().getX() << " , " << getPosition().getY() << " ";
	// 	curPos << "Height: " << box.getVertical() << " , " << "Width: " << box.getHorizontal();
	// 	graphics_manager.drawString(Position(0, 23), curPos.str(), LEFT_JUSTIFIED);
	// 	ResourceManager& resMgr = ResourceManager::getInstance();
	// 	Sprite* a = resMgr.getSprite("platform");
	// 	Frame b = a->getFrame(0);
	// 	graphics_manager.drawFrame(this->getPosition(), b, true, false, a->getColor());
	//graphics_manager.drawCh(getPosition(), SAUCER_CHAR, COLOR_GREEN); 
}
