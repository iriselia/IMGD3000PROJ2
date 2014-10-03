#include "Sprite.h"

Sprite::Sprite(int max_frames) :
Sprite()
{
	max_frame_count = max_frames;
	frame = (Frame*)malloc(sizeof(Frame)* max_frames);
	memset(frame, 0, sizeof(Frame)*max_frames);
}

Sprite::Sprite()
{
	width = 0;
	height = 0;
	max_frame_count = 0;
	frame_count = 0;
	color = 0;
	frame = nullptr;
	label = "";
}

Sprite::~Sprite()
{
	if (frame_count)
	{
		delete frame;
	}
}

