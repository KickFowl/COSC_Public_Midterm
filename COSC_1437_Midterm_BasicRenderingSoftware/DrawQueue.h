#pragma once
#include <iostream>
#include <vector>
#include <functional>

#include "dataStructs.h"
#include "Color.h"

struct span
{
	COLOR color;
	coord2D start;
	int length, z_index;
};

class DrawQueue
{
	std::vector<span> drawQueue;

public:

	int getQueueLength() { return drawQueue.size(); }
	span getQueueAt(int index) { return drawQueue[index]; }

	void clearQueue() { drawQueue.clear(); }
	void pushToQueue(coord2D start, int length, COLOR color = colors::green, int z_index = 5) { drawQueue.push_back(span{ color, start, length, z_index }); }

};
