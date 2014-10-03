#include "InputManager.h"
#include "EventKeyboard.h"
#include "EventMouse.h"
#include "LogManager.h"
#include "curses.h"

InputManager::InputManager()
{

}

void InputManager::getInput()
{
	// Check for input.
	int key = getch();
	if (key != ERR)
	{
		MEVENT m_event;
		if (key == KEY_MOUSE && nc_getmouse(&m_event) == OK)
		{
			// Mouse, m_event has values.
			if (m_event.bstate & BUTTON1_CLICKED)
			{
				EventMouse newEvent;
				newEvent.setMouseX(m_event.x);
				newEvent.setMouseY(m_event.y);
				newEvent.setMouseAction(LEFT_BUTTON_CLICK);
				onEvent(&newEvent);
			}
		}
		else
		{
			EventKeyboard newEvent;
			newEvent.setKey(key);
			onEvent(&newEvent);
		}
	}
}

void InputManager::shutDown()
{
	auto& logManager = LogManager::getInstance();
	logManager.writeLog("Input Manager: shutting down.\n");
}

int InputManager::startUp()
{
	int hr = 0;
	// Normal terminal input buffers until \n or \r, so disable.
	hr |= cbreak();
	hr |= nodelay(stdscr, TRUE);

	// Disable newline so can detect ¡°enter¡± key.
	hr |= nonl();
	// Turn off cursor.
	hr |= curs_set(0);
	// Disable character echo.
	hr |= noecho();
	// Enable mouse events ¨C setup mask.
	mousemask(BUTTON1_CLICKED, NULL);
	// Other mousemask calls, as needed¡­
	// Enable keypad.
	hr |= keypad(stdscr, TRUE);
	if (hr)
	{
		printf("Fatal error: InputManager failed to start up.\n");
		return ERR;
	}
	else
	{
		auto& logger = LogManager::getInstance();
		logger.writeLog("Input Manager:: starting up.\n");
		return OK;
	}
}

bool InputManager::isValid(string event_type) const
{
	return event_type == DF_KEYBOARD_EVENT ||
		event_type == DF_MOUSE_EVENT;
}

