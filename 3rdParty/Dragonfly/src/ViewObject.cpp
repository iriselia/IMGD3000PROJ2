#include "ViewObject.h"

void ViewObject::draw()
{
	auto& gfxMgr = GraphicsManager::getInstance();
	std::stringstream temp_str;
	// Display view string + value.
	if (border)
	{
		temp_str << "|" << getViewString() << " " << value << "|";
	}
	else
	{
		temp_str << getViewString() << " " << value;
	}
	// Draw centered at position.
	Position pos = viewToWorld(getPosition());
	gfxMgr.drawString(pos, temp_str.str(), CENTER_JUSTIFIED, getColor());
	if (border)
	{
		int x = pos.getX();
		int y = pos.getY();
		int length = temp_str.str().length();
		std::stringstream frameStr;
		for (int i = 0; i < length; i++)
		{
			frameStr << "=";
		}
		// Draw box around display.
		gfxMgr.drawString(Position(x, y - 1), frameStr.str(), CENTER_JUSTIFIED, getColor());
		gfxMgr.drawString(Position(x, y + 1), frameStr.str(), CENTER_JUSTIFIED, getColor());
	}
}

void ViewObject::setLocation(ViewObjectLocation new_location)
{
	auto& worldMgr = WorldManager::getInstance();
	int delta = 0;
	Position p;
	// Set new position based on location.
	if (!getBorder())
	{
		delta = -1;
	}

	switch (new_location)
	{
	case TOP_LEFT:
		p.setXY(worldMgr.getView().getHorizontal() * 1 / 6, 1);
		break;
	case TOP_CENTER:
		p.setXY(worldMgr.getView().getHorizontal() * 3 / 6, 1);
		break;
	case TOP_RIGHT:
		p.setXY(worldMgr.getView().getHorizontal() * 6 / 6, 1);
		break;
	}

	// Shift, as needed, based on border.
	p.setY(p.getY() + delta);
	// Set position of object to new position.
	setPosition(p);
}

int ViewObject::eventHandler(Event *p_e)
{
	// See if this is a `view' event.
	if (p_e->getType() == DF_VIEW_EVENT)
	{
		EventView *p_ve = static_cast <EventView *> (p_e);
		// See if this event is meant for this object.
		if (p_ve->getTag() == getViewString())
		{
			if (p_ve->getDelta())
			{
				setValue(getValue() + p_ve->getValue()); // Change in value.
			}
			else
			{
				setValue(p_ve->getValue()); // New value.
			}
		}

		// Event was handled.
		return 1;
	}



	// If here, event was not handled.
	return 0;
}

