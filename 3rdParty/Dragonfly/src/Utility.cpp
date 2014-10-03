#include "utility.h"
#include "WorldManager.h"

Box getWorldBox(Object *p_o)
{
	Box box = p_o->getBox();
	Position corner = box.getCorner();
	int x = corner.getX() + p_o->getPosition().getX();
	int y = corner.getY() + p_o->getPosition().getY();
	if (p_o->isCentered())
	{
		if (p_o->getSprite())
		{
			x -= p_o->getSprite()->getWidth() / 2;
			y -= p_o->getSprite()->getHeight() / 2;
		}
	}
	corner.setXY(x, y);
	box.setCorner(corner);
	return box;
}

Box getWorldBox(Object *p_o, Position where)
{
	Box box = p_o->getBox();
	Position corner = box.getCorner();
	int x = corner.getX() + where.getX();
	int y = corner.getY() + where.getY();
	if (p_o->isCentered())
	{
		if (p_o->getSprite())
		{
			x -= p_o->getSprite()->getWidth() / 2;
			y -= p_o->getSprite()->getHeight() / 2;
		}
	}
	corner.setXY(x, y);
	box.setCorner(corner);
	return box;
}

Position worldToView(Position world_pos)
{
	auto& worldMgr = WorldManager::getInstance();
	auto view_origin = worldMgr.getView().getCorner();
	int view_x = view_origin.getX();
	int view_y = view_origin.getY();
	Position view_pos(world_pos.getX() - view_x, world_pos.getY() - view_y);
	return view_pos;
}

Position viewToWorld(Position view_pos)
{
	auto& worldMgr = WorldManager::getInstance();
	auto view_origin = worldMgr.getView().getCorner();
	int view_x = view_origin.getX();
	int view_y = view_origin.getY();
	Position new_pos(view_pos.getX() + view_x, view_pos.getY() + view_y);
	return new_pos;
}

