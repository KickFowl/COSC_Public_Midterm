#include "DrawQueue.h"

void DrawQueue::pushToQueue(coord2D start, int length, const COLOR& color, int z_index)
{

	if (length <= 0)
	{
		length = -length;
		start.x -= length;
	}


	drawQueue.push_back(span{ color, start, length, z_index });
}

void DrawQueue::pushToQueue(span newSpan)
{
	if (newSpan.length <= 0)
	{
		newSpan.length = -newSpan.length;
		newSpan.start.x -= newSpan.length;
	}


	drawQueue.push_back(newSpan);
}
