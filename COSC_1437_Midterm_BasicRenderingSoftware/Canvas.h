#pragma once

#include <array>
#include <vector>

#include "WindowManager.h"
#include "dataStructs.h"
#include "DrawQueue.h"
#include "Color.h"

class Canvas
{
	uint32_t backgroundColor = 0xFF000000;

	int width, height;

protected:
	WindowManager& context;

	//std::array<coord, 3> polygonSortX(polygon& poly);
	//std::array<coord, 3> polygonSortY(polygon& poly);

	bool alongLine(coord insert, coord p1, coord p2);

	void inline setContext(WindowManager& newContext) { context = newContext; };
public:
	Canvas(WindowManager& context);

	DrawQueue drawQueue;

	const inline WindowManager& getContext() { return context; };
	
	inline int getWidth() { return context.getWidth(); };
	inline int getHeight() { return context.getHeight(); };

	void setBackground(uint32_t color);
	void setPixelColor(coord& pos, const COLOR& color = colors::green);

	void draw();

};

