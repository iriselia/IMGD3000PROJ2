#include "GraphicsManager.h"
#include "WorldManager.h"
#include "LogManager.h"

GraphicsManager::GraphicsManager()
{
}

WINDOW * GraphicsManager::getCurrentBuffer() const
{
	return p_buffer == buffer1 ? buffer2 : buffer1;
}

WINDOW * GraphicsManager::getPreviousBuffer() const
{
	return p_buffer;
}

int GraphicsManager::swapBuffers()
{
	int hr = 0;

	//redraw
	hr = wrefresh(p_buffer);
	//swap buffer
	if (p_buffer == buffer1)
		p_buffer = buffer2;
	else
		p_buffer = buffer1;
	//erase screen
	hr = werase(p_buffer);

	if (!hr)
		return 0;
	else
		return -1;
}

int GraphicsManager::getVertical() const
{
	return getmaxx(stdscr);
}

int GraphicsManager::getHorizontal() const
{
	return getmaxy(stdscr);
}

int GraphicsManager::drawString(Position world_pos, string str, Justification just, int color /*= DF_COLOR_DEFAULT*/) const
{
	int hr;

	Position start_pos = world_pos;
	switch (just)
	{
	case LEFT_JUSTIFIED:
		break;
	case CENTER_JUSTIFIED:
		start_pos.setX(world_pos.getX() - str.size() / 2);
		break;
	case RIGHT_JUSTIFIED:
		start_pos.setX(world_pos.getX() - str.size());
		break;
	default:
		break;
	}
	wattron(p_buffer, COLOR_PAIR(color));
	//Draw character by character
	for (int i = 0; i < str.size(); i++)
	{
		Position temp_pos(start_pos.getX() + i, start_pos.getY());
		hr = drawCh(temp_pos, str[i], color);
	}
	wattroff(p_buffer, COLOR_PAIR(color));

	if (!hr)
		return 0;
	else
		return -1;
}

int GraphicsManager::drawCh(Position world_pos, char ch, int color /*= DF_COLOR_DEFAULT*/) const
{
	int hr;

	Position view_pos = worldToView(world_pos);

	wattron(p_buffer, COLOR_PAIR(color));
	hr = mvwaddch(p_buffer, view_pos.getY(), view_pos.getX(), ch);
	wattroff(p_buffer, COLOR_PAIR(color));
	if (!hr)
		return 0;
	else
		return -1;
}

void GraphicsManager::shutDown()
{
	delwin(buffer1);
	delwin(buffer2);
	endwin();
	bool down = isendwin();

	auto& logManager = LogManager::getInstance();
	logManager.writeLog("Graphics Manager: shutting down.\n");
}

int GraphicsManager::startUp()
{
	int hr;
	hr = (int)(initscr());
	if (!hr) printf("curses failed to initialize.\n");

	resize_term(40, 200);

	//Create windows
	int x, y;
	getmaxyx(stdscr, y, x);
	buffer1 = newwin(y, x, 0, 0);
	hr = clearok(buffer1, TRUE);
	if (hr) printf("curses failed to initialize clearok.\n");
	hr = leaveok(buffer1, TRUE);
	if (hr) printf("curses failed to initialize leaveok.\n");

	p_buffer = buffer1;

	buffer2 = newwin(y, x, 0, 0);
	hr = clearok(buffer2, TRUE);
	if (hr) printf("curses failed to initialize clearok.\n");
	hr = leaveok(buffer2, TRUE);
	if (hr) printf("curses failed to initialize leaveok.\n");

	auto& worldManager = WorldManager::getInstance();
	worldManager.setBoundary(Box(Position(0, 0), 2000, 2000));

	//Set colors
	if (has_colors())
	{
		hr = start_color();
		if (hr) printf("curses failed to initialize start color.\n");
		hr = init_pair(COLOR_RED, COLOR_RED, COLOR_BLACK);
		init_pair(COLOR_GREEN, COLOR_GREEN, COLOR_BLACK);
		init_pair(COLOR_YELLOW, COLOR_YELLOW, COLOR_BLACK);
		init_pair(COLOR_BLUE, COLOR_BLUE, COLOR_BLACK);
		init_pair(COLOR_MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
		init_pair(COLOR_CYAN, COLOR_CYAN, COLOR_BLACK);
		init_pair(COLOR_WHITE, COLOR_WHITE, COLOR_BLACK);
		if (hr) printf("curses failed to initialize colors.\n");
	}
	//Bold
	hr = wattron(buffer1, A_BOLD);
	if (hr) printf("curses failed to initialize wattron.\n");
	hr = wattron(buffer2, A_BOLD);
	if (hr) printf("curses failed to initialize wattron.\n");


	//start up base
	hr = Manager::startUp();
	if (hr) printf("curses failed to initialize wattron.\n");

	auto& logger = LogManager::getInstance();
	logger.writeLog("Graphics Manager:: starting up.\n");
	//return
	if (!hr)
		return 0;
	else
		return -1;
}

