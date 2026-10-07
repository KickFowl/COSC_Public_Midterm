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

	std::array<coord2D, 3> polygonSortX(polygon2D& poly);
	std::array<coord2D, 3> polygonSortY(polygon2D& poly);

	bool alongLine(coord2D insert, coord2D p1, coord2D p2);

	void inline setContext(WindowManager& newContext) { context = newContext; };
public:
	Canvas(WindowManager& context);

	DrawQueue drawQueue;

	const inline WindowManager& getContext() { return context; };
	
	inline int getWidth() { return context.getWidth(); };
	inline int getHeight() { return context.getHeight(); };

	void setBackground(uint32_t color);
	void setPixelColor(coord2D& pos, const COLOR& color = colors::green);

	void draw2D();

};

