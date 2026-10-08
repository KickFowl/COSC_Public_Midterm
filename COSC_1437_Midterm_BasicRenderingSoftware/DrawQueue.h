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
	std::vector<std::variant<span, vertex>> drawQueue;

	int getQueueLength() { return drawQueue.size(); }
	std::variant<span, vertex> getQueueAt(int index) { return drawQueue[index]; }

	void clearQueue() { drawQueue.clear(); }
	void pushSpan(coord2D start, int length, const COLOR& color = colors::green, int z_index = 5);
	void pushSpan(span newSpan);
	void pushVert(coord2D pos, const COLOR& color = colors::green, int z_index = 5);
	void pushVert(vertex vert) { drawQueue.push_back(vert); }
};
