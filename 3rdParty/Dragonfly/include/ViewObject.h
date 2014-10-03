///
/// The view object
///

#pragma once

#include <string>

using std::string;

#include "Event.h"        
#include "Object.h"
#include "GraphicsManager.h"
#include "EventView.h"
#include "WorldManager.h"
#include <sstream>
#include "utility.h"

/// Count of number of view object modified attribute categories.
#define DF_VATTR_COUNT 5

/// Categories of view object attributes that indicate modification.
enum ViewObjectAttribute
{
	VIEW_STRING,
	VALUE,
	BORDER,
	COLOR,
	LOCATION,
};

/// General location of ViewObject on screen.
enum ViewObjectLocation
{
	TOP_LEFT,
	TOP_CENTER,
	TOP_RIGHT,
	CENTER_CENTER,
	BOTTOM_LEFT,
	BOTTOM_CENTER,
	BOTTOM_RIGHT,
};

class ViewObject : public Object
{

private:
	string view_string;   ///< Label for value (e.g., "Points").
	int value;            ///< Value displayed (e.g., points).
	bool border;          ///< True if border around display.
	int color;            ///< Color for text.
	ViewObjectLocation location; ///< Location of ViewObject.
	bool vmodified[DF_VATTR_COUNT]; ///< Mod. attrib. since serialize().

public:
	/// Construct ViewObject. 
	/// Object settings: SPECTRAL, max altitude.
	/// ViewObject defaults: border, top_center, default color.
	ViewObject()
	{
		// Initialize Object attributes.
		setSolidness(SPECTRAL);
		setAltitude(DF_MAX_ALTITUDE);
		setType("ViewObject");
		// Initialize ViewObject attributes.
		setValue(0);
		setBorder(true);
		setLocation(TOP_CENTER);
		setColor(DF_COLOR_DEFAULT);
		setBox(Box(Position(), 0, 0));
		setSprite(nullptr);
		// Register interest in view events (EVENTVIEW).
		registerInterest(DF_VIEW_EVENT);
		// default;
	}

	/// Draw view string and value.
	virtual void draw();

	/// Handle "view" event if tag matches view_string (others ignored).
	/// Return 0 if ignored, else 1.
	virtual int eventHandler(Event *p_e);

	/// Set general location of ViewObject on screen.
	void setLocation(ViewObjectLocation new_location);

	/// Get general location of ViewObject on screen.
	ViewObjectLocation getLocation() const
	{
		return location;
	}

	/// Set view value.
	void setValue(int new_value)
	{
		value = new_value;
	}

	/// Get view value.
	int getValue() const
	{
		return value;
	}

	/// Set view border (true = display border).
	void setBorder(bool new_border)
	{
		border = new_border;
	}

	/// Get view border (true = display border).
	bool getBorder() const
	{
		return border;
	}

	/// Set view color.
	void setColor(int new_color)
	{
		color = new_color;
	}

	/// Get view color.
	int getColor() const
	{
		return color;
	}

	/// Set view display string.
	void setViewString(string new_view_string)
	{
		view_string = new_view_string;
	}

	/// Get view display string.
	string getViewString() const
	{
		return view_string;
	}

	/// Serialize ViewObject attributes to a single string.
	/// Only modified attributes (unless all is true).
	virtual string serialize(bool all = false)
	{
		return "";
	}

	/// Deserialize string to become Object attributes.
	/// Rerturn 0 if no errors, else -1.  
	virtual int deserialize(string s)
	{
		return 0;
	}

	/// Return true if attribute modified since last serialize.
	virtual bool isModified(enum ViewObjectAttribute attribute) const
	{
		return false;
	}

	/// Return true if any attribute modified since last serialize.
	virtual bool isModified() const
	{
		return false;
	}
};
