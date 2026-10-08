#pragma once

#include "Canvas.h"
#include "dataStructs.h"

class TwoDimensional
{

protected:

	Canvas& canvas;

public:

	TwoDimensional(Canvas& canvas) : canvas(canvas) {}

	void drawLine(const coord2D& pos1, const coord2D& pos2, const COLOR& color = colors::green);

	void drawPolygon(const polygon2D& poly, const COLOR& color = colors::green);

	void drawQuad(const quad2D& quad, const COLOR& color);

	void drawRect(const coord2D& start, int width, int height, const COLOR& color, alignment alightTo = alignment::TOPLEFT);


	void fillQuad(const quad2D& quad);
	void fillRect(const coord2D& topLeft, int width, int height, const COLOR& color);

};

