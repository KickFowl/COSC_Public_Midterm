#pragma once
#include <iostream>
#include <vector>
#include <functional>

#include "dataStructs.h"
#include "Color.h"

class DrawQueue
{
	std::vector<span> drawQueue;

public:

	int getQueueLength() { return drawQueue.size(); }
	span getQueueAt(int index) { return drawQueue[index]; }

	void clearQueue() { drawQueue.clear(); }
	void pushToQueue(coord2D start, int length, const COLOR& color = colors::green, int z_index = 5);
	void pushToQueue(span newSpan);

};
