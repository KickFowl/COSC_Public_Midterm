#pragma once

#include <array>
#include <vector>

#include "WindowManager.h"
#include "dataStructs.h"

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

	//std::vector<coord2D> drawQueue2D;

	int width, height;

protected:
	WindowManager& context;

	std::array<coord2D, 3> polygonSortX(polygon2D& poly);
	std::array<coord2D, 3> polygonSortY(polygon2D& poly);

	bool alongLine(coord2D insert, coord2D p1, coord2D p2);

	quad2D polygonBound2D(polygon2D& poly);
	quad2D nongonBound2D(nongon2D& non);

	void inline setContext(WindowManager& newContext) { context = newContext; };
public:
	Canvas(WindowManager& context);

	const inline WindowManager& getContext() { return context; };
	
	inline int getWidth() { return context.getWidth(); };
	inline int getHeight() { return context.getHeight(); };

	void setBackground(uint32_t color);
	void setPixelColor(coord2D& pos);

	void drawLine2D(coord2D& pos1, coord2D& pos2);
	void drawLine2D(coord2D& pos1, coord2D& pos2, const COLOR& color);

	void drawPolygon2D(polygon2D& poly);
	void fanFillPolygon2D(polygon2D& poly);
	void polygon2DRasterizer(polygon2D& poly, bool debug = false);

	void drawQuad2D(quad2D& quad);

	void drawRect2D(coord2D& start, int width, int height, alignment alignTo = alignment::TOPLEFT);
	void drawRect2D(coord2D& start, int width, int height, const COLOR& color, alignment alightTo = alignment::TOPLEFT);


	void fillQuad2D(quad2D& quad);
	void fillRect2D(coord2D& topLeft, int width, int height);

	void draw2D();

};

