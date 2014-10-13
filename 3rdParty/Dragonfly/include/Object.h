///
/// The base game world object
///

#pragma once

#include <string>

#include "Box.h"              ///< Objects have a bounding box.
#include "Event.h"            ///< Objects can handle events.
#include "Position.h"         ///< Objects need a location.
#include "Sprite.h"           ///< Objects (often) have sprites.

#define DF_MAX_ALTITUDE 4      ///< Drawing order 0 to max.
#define DF_MAX_OBJ_EVENTS 100 ///< Max events Object can be interested in.

using std::string;            // Introduce "string" into namespace

#define random rand

/// Types of solidness of Object.
enum Solidness
{
	HARD,       ///< Object causes collisions and impedes.
	SOFT,       ///< Object causes collision, but doesn't impede.
	SPECTRAL    ///< Object doesn't cause collisions.
};

/// Count of number of modified attribute categories.
#define DF_ATTR_COUNT 12

/// Categories of attributes that indicate modification.
enum ObjectAttribute
{
	ID,
	ACTIVE,
	VISIBLE,
	EVENTS,
	BOX,
	POS,
	TYPE,
	SPRITE,
	ALTITUDE,
	SOLIDNESS,
	NO_SOFT,
	VELOCITY,
};

class Object
{

private:
	int id;		      ///< Unique Object id.
	bool is_active;             ///< If false, Object not acted upon.
	bool is_visible;            ///< If true, Object gets drawn.
	int event_count;            ///< Number of events of interest.
	string event_name[DF_MAX_OBJ_EVENTS]; ///< Event names.
	Box box;                    ///< Box for sprite boundary & collisions.
	Position pos;               ///< Position in the game world.
	string type;                ///< User-defined identification.
	string sprite_name;	      ///< Sprite name in ResourceManager.
	Sprite *p_sprite;           ///< Sprite associated with Object.
	bool sprite_center;         ///< True if sprite centered on Object.
	char sprite_transparency;   ///< Sprite transparent character (0 if none).
	int sprite_index;           ///< Current index frame for sprite.
	int sprite_slowdown;        ///< Slowdown rate (1 = no slowdown, 0 = stop).
	int sprite_slowdown_count;  ///< Slowdown counter.
	int altitude;               ///< 0 to MAX_ALTITUDE (lower drawn first).
	Solidness solidness;        ///< Solidness state of Object.
	bool no_soft;               ///< True if won't move on soft Objects.
	float x_velocity;           ///< Horizontal speed in spaces per game step.
	float x_velocity_countdown; ///< Countdown to horizontal movement.
	float y_velocity;           ///< Vertical speed in spaces per game step.
	float y_velocity_countdown; ///< Countdown to vertical movement.
	bool modified[DF_ATTR_COUNT]; ///< Mod. attrib. since serialize().
	bool onPlatform;

public:
	/// Construct Object. Set default parameters and
	/// add to game world (WorldManager).
	Object();

	/// Destroy Object. Unregister for any interested events.
	/// Remove from game world (WorldManager).
	virtual ~Object();

	/// Set Object id.
	void setId(int new_id)
	{
		id = new_id;
	}

	bool getOnPlataform()
	{
		return onPlatform;
	}

	void setOnPlataform(bool onn)
	{
		onPlatform = onn;
	}
	/// Get Object id.
	int getId() const
	{
		return id;
	}

	/// Set type identifier of Object.
	void setType(string new_type)
	{
		this->type = new_type;
	}

	/// Get type identifier of Object.
	string getType() const
	{
		return type;
	}

	///< Return True if Object is HARD or SOFT, else False.
	bool isSolid() const
	{
		return solidness == HARD || solidness == SOFT;
	}

	/// Set solidness of Object, with checks for consistency.  
	/// Return 0 if ok, else -1.
	int setSolidness(Solidness new_solid)
	{
		solidness = new_solid;
		return 0;
	}

	/// Return solidness of Object.
	Solidness getSolidness() const
	{
		return solidness;
	}

	/// Set visibility of Object.  Objects not visible are not drawn.
	/// Return 0 if ok, else -1.
	int setVisible(bool visible = true)
	{
		this->is_visible = visible;
	}

	/// Return visibility of Object.  Objects not visible are not drawn.
	bool isVisible() const
	{
		return is_visible;
	}

	/// Set activeness of Object.  Objects not active are not acted upon
	/// by engine.
	/// Return 0 if ok, else -1.
	int setActive(bool active = true)
	{
		is_active = active;
		return 0;
	}

	/// Return activeness of Object.  Objects not active are not acted upon
	/// by engine.
	bool isActive() const
	{
		return is_active;
	}

	/// Set altitude of Object, with checks for range [0, MAX_ALTITUDE].
	/// Return 0 if ok, else -1.
	int setAltitude(int new_altitude)
	{
		if (new_altitude >= 0 &&
			new_altitude <= DF_MAX_ALTITUDE)
		{
			this->altitude = new_altitude;
			return 1;
		}
		else
		{
			return -1;
		}
	}

	/// Return altitude of Object.
	int getAltitude() const
	{
		return altitude;
	}

	/// Set x velocity of Object.
	void setXVelocity(float new_x_velocity)
	{
		x_velocity = new_x_velocity;
	}

	/// Get x velocity of Object.
	float getXVelocity() const
	{
		return x_velocity;
	}

	/// Set y velocity of Object.
	void setYVelocity(float new_y_velocity)
	{
		y_velocity = new_y_velocity;
	}

	/// Get y velocity of Object.
	float getYVelocity() const
	{
		return y_velocity;
	}

	/// Perform 1 step of velocity in horizontal direction.
	/// Return horizontal distance moved this step.
	int getXVelocityStep()
	{
		if (!x_velocity)
		{
			return 0;
		}

		x_velocity_countdown -= fabs(x_velocity);
		if (x_velocity_countdown > 0)
		{
			return 0;
		}

		// Moving this step, so figure out how far.
		int spaces = (int)floor(1 - x_velocity_countdown);
		x_velocity_countdown = (float)(1 + fmod(x_velocity_countdown, 1));
			// Return number of spaces to move.
		if (x_velocity > 0)
		{
			return spaces;
		}
		else
		{
			return -spaces;
		}
	}

	/// Perform 1 step of velocity in vertical direction.
	/// Return vertical distance moved this step.
	int getYVelocityStep()
	{
		if (!y_velocity)
		{
			return 0;
		}

		y_velocity_countdown -= fabs(y_velocity);
		if (y_velocity_countdown > 0)
		{
			return 0;
		}

		// Moving this step, so figure out how far.
		int spaces = (int)floor(1 - y_velocity_countdown);
		y_velocity_countdown = (float)(1 + fmod(y_velocity_countdown, 1));
		// Return number of spaces to move.
		if (y_velocity > 0)
		{
			return spaces;
		}
		else
		{
			return -spaces;
		}
	}

	/// Set "no soft" setting of Object (true - cannot move onto SOFT Objects).
	void setNoSoft(bool new_no_soft = true)
	{
		this->no_soft = new_no_soft;
	}

	/// Get "no soft" setting of Object (true - cannot move onto SOFT Objects).
	bool getNoSoft() const
	{
		return no_soft;
	}

	/// Set bounding box of Object.
	void setBox(Box new_box)
	{
		this->box = new_box;
	}

	/// Get bounding box of Object.
	Box getBox() const
	{
		return box;
	}

	/// Set Position of Object.
	void setPosition(Position new_pos)
	{
		pos = new_pos;
	}

	/// Get Position of Object.
	Position getPosition() const
	{
		return pos;
	}

	/// Handle event (default is to ignore everything).
	/// Return 0 if ignored, else 1.
	virtual int eventHandler(Event *p_event);

	/// Register for interest in event.  
	/// Keeps track of manager and event.  
	/// Return 0 if ok, else -1.
	int registerInterest(string event_type);

	/// Unregister for interest in event.  
	/// Return 0 if ok, else -1.
	int unregisterInterest(string event_type);

	/// Draw single Sprite Frame.
	/// Drawing accounts for: centering, slowdown, advancing Sprite Frame.
	virtual void draw();

	/// Set Sprite name (in ResourceManager) for Object.
	void setSpriteName(string new_name)
	{
		this->sprite_name = new_name;
	}

	/// Get Sprite name (in ResourceManager) for Object.
	string getSpriteName() const
	{
		return sprite_name;
	}

	/// Set Object Sprite to new one.
	/// If set_box is true, set bounding box to size of Sprite.
	/// Set sprite index to 0 (first frame).
	void setSprite(Sprite *p_new_sprite, bool set_box = true)
	{
		this->p_sprite = p_new_sprite;
		if (set_box)
		{
			//
		}
	}

	/// Return pointer to Sprite associated with this Object.
	Sprite *getSprite() const
	{
		return p_sprite;
	}

	/// Set Sprite to be centered at Object position (pos).
	void setCentered(bool centered = true)
	{
		this->sprite_center = centered;
	}

	/// Indicates if Sprite is centered at Object position (pos).
	bool isCentered() const
	{
		return sprite_center;
	}

	/// Set Sprite transparency character (0 means none).
	void setTransparency(char transparent = ' ')
	{
		this->sprite_transparency = transparent;
	}

	/// Get Sprite transparency character (0 means none).
	char getTransparency() const
	{
		return sprite_transparency;
	}

	/// Set index of current Sprite frame to be displayed.
	void setSpriteIndex(int new_sprite_index)
	{
		this->sprite_index = new_sprite_index;
	}

	/// Return index of current Sprite frame to be displayed.
	int getSpriteIndex() const
	{
		return sprite_index;
	}

	/// Slows down sprite animations.
	/// Slowdown value in multiples of WorldManager frame time.
	void setSpriteSlowdown(int new_sprite_slowdown)
	{
		this->sprite_slowdown = new_sprite_slowdown;
	}
	int getSpriteSlowdown() const
	{
		return sprite_slowdown;
	}
	void setSpriteSlowdownCount(int new_sprite_slowdown_count)
	{
		this->sprite_slowdown_count = new_sprite_slowdown_count;
	}
	int getSpriteSlowdownCount() const
	{
		return sprite_slowdown_count;
	}

	/// Serialize Object attributes to single string.
	/// e.g., "id:110,is_active:true, ...
	/// Only modified attributes are serialized (unless all is true).
	/// Clear modified[] array.
	virtual string serialize(bool all = false);

	/// Deserialize string to become Object attributes.
	/// Return 0 if no errors, else -1.  
	virtual int deserialize(string s);

	/// Return true if attribute modified since last serialize.
	virtual bool isModified(enum ObjectAttribute attribute) const;

	/// Return true if any attribute modified since last serialize.
	virtual bool isModified() const;
};