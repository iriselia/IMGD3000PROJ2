#include "ResourceManager.h"
#include "LogManager.h"
#include "Frame.h"
#include <fstream>
#include <iostream>
#include <algorithm>

int ResourceManager::unloadSprite(string label)
{
	for (int i = 0; i <= sprite_count; i++)
	{
		if (p_sprite[i]->getLabel() == label)
		{
			delete p_sprite[i];
			p_sprite[i] = nullptr;
			sprite_count--;

			//sort the list
			//sort the objects
			int i;
			int openSlot = -1;
			for (i = 0; i < DF_MAX_SPRITES; i++)
			{
				if (openSlot == -1 && p_sprite[i] == nullptr)
				{
					openSlot = i;
				}
				else if (openSlot != -1 && p_sprite[i] != nullptr)
				{
					p_sprite[openSlot] = p_sprite[i];
					p_sprite[i] = nullptr;
					openSlot = i;
				}
			}
			return 0;
		}
	}

	//something went wrong
	return -1;
}

std::string getStr(std::ifstream& _file, int& _lineNum, const char* _tag)
{
	std::string line;
	std::getline(_file, line);
	std::string delim = " ";
	size_t pos = 0;
	pos = line.find(delim);


	if (pos == std::string::npos)
	{
		//delimiter not found
		return "";
	}
	else
	{
		std::string tag = line.substr(0, pos);
		if (tag != _tag)
		{
			//tag mismatch
			return "";
		}
		else
		{
			line.erase(0, pos + delim.length());
			_lineNum++;
			return line.c_str();
		}
	}
}

int getInt(std::ifstream& _file, int& _lineNum, const char* _tag)
{
	std::string result = getStr(_file, _lineNum, _tag);
	if (result == "")
	{
		return -1;
	}
	else
	{
		return atoi(result.c_str());
	}
}

Frame readFrame(std::ifstream& _file, int& _lineNum, int _width, int _height)
{
	std::string line;
	std::stringstream iss;

	while (line != DF_END_FRAME_TOKEN)
	{
		getline(_file, line);
		if (line == DF_END_SPRITE_TOKEN)
		{
			return Frame(0, 0, DF_END_SPRITE_TOKEN);
		}
		else if (line != DF_END_FRAME_TOKEN)
		{
			iss << line;
		}

	}
	auto rFrame = Frame(_width, _height, iss.str());
	return rFrame;
}

int ResourceManager::loadSprite(string filename, string label)
{
	auto& logManager = LogManager::getInstance();

	for (int i = 0; i < sprite_count; i++)
	{
		if (p_sprite[i])
		{
			if (p_sprite[i]->getLabel() == label)
			{
				logManager.writeLog("Sprite: %s already loaded.\n", filename.c_str());
				return -1;
			}
		}
	}
	//start reading sprite file
	std::string line;
	std::ifstream file;
	int lineNum = 0;
	file.open(filename);

	if (!file.is_open())
	{
		logManager.writeLog("file %s\n", filename.c_str());
		logManager.writeLog("Failed to open sprite file.\n");
		return -1;
	}

	int frames = getInt(file, lineNum, "frames");
	int width = getInt(file, lineNum, "width");
	int height = getInt(file, lineNum, "height");
	int icolor = 7; //color white
	std::string color = getStr(file, lineNum, "color");
	std::transform(color.begin(), color.end(), color.begin(), ::tolower);

	if (color == "black")
	{
		icolor = 0;
	}
	else if (color == "blue")
	{
		icolor = 1;
	}
	else if (color == "green")
	{
		icolor = 2;
	}
	else if (color == "red")
	{
		icolor = 4;
	}
	else if (color == "cyan")
	{
		icolor = 1 | 2;
	}
	else if (color == "magenta")
	{
		icolor = 1 | 4;
	}
	else if (color == "yellow")
	{
		icolor = 2 | 4;
	}
	else if (color == "white")
	{
		icolor = 7;
	}
	else
	{
		//not found
		icolor = -1;
	}

	if (frames == -1 ||
		width == -1 ||
		height == -1 ||
		icolor == -1)
	{
		logManager.writeLog("file %s\n", filename.c_str());
		logManager.writeLog("Sprite: %s header parse error.\n", filename.c_str());
	}

	auto* newSpr = new Sprite(frames);
	newSpr->setLabel(label);
	newSpr->setWidth(width);
	newSpr->setHeight(height);
	newSpr->setColor(icolor);
	
	Frame frame;
	//read frames
	do
	{
		frame = readFrame(file, lineNum, width, height);
		if (frame.getString() != "eof")
		{
			if (newSpr->addFrame(frame) == -1)
			{
				logManager.writeLog("Too many sprite frames in file: %s.\n", filename.c_str());
				return -1;
			}
		}
	} while (frame.getString() != "eof");

	//add sprite to list

	for (int i = 0; i <= sprite_count; i++)
	{
		if (p_sprite[i] == nullptr)
		{
			p_sprite[i] = newSpr;
			sprite_count++;
			return 0;
		}
	}

	logManager.writeLog("Resource Manager: too many sprites in the sprite container.\n", filename.c_str());
	return -1;
}