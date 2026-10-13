#pragma once
#include <iostream>
#include <vector>
#include <functional>
#include <variant>

#include "dataStructs.h"
#include "Color.h"

class DrawQueue
{

public:
	std::vector<vertex> drawQueue;

	int getQueueLength() { return drawQueue.size(); }
	vertex getQueueAt(int index) { return drawQueue[index]; }

	void clearQueue() { drawQueue.clear(); }

	void pushVert(coord pos, const COLOR& color = colors::green, int z_index = 5) { drawQueue.push_back(vertex{ color, pos, z_index }); };
	void pushVert(vertex vert) { drawQueue.push_back(vert); }
};
