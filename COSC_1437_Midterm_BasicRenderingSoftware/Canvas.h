#pragma once

#include <array>
#include <vector>

#include "WindowManager.h"
#include "dataStructs.h"
#include "DrawQueue.h"

enum class alignment {
	TOPLEFT,
	TOPRIGHT,
	BOTTOMLEFT,
	BOTTOMRIGHT,
	CENTER
};

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
	void setPixelColor(coord2D& pos, COLOR& color = colors::green);

	void drawPolygon2D(polygon2D& poly);

	void drawQuad2D(quad2D& quad);

	void drawRect2D(coord2D& start, int width, int height, alignment alignTo = alignment::TOPLEFT);
	void drawRect2D(coord2D& start, int width, int height, const COLOR& color, alignment alightTo = alignment::TOPLEFT);


	void fillQuad2D(quad2D& quad);
	void fillRect2D(coord2D& topLeft, int width, int height);

	void draw2D();

};

