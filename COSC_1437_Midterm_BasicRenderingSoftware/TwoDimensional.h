#pragma once

#include "Canvas.h"
#include "dataStructs.h"

class TwoDimensional
{

	Canvas& canvas;

protected:

public:

	TwoDimensional(Canvas& canvas) : canvas(canvas) {}

	void drawLine(coord2D& pos1, coord2D& pos2, const COLOR& color = colors::green);

	void drawPolygon(polygon2D& poly, const COLOR& color = colors::green);

	void drawQuad(quad2D& quad, const COLOR& color);

	void drawRect(coord2D& start, int width, int height, const COLOR& color, alignment alightTo = alignment::TOPLEFT);


	void fillQuad(quad2D& quad);
	void fillRect(coord2D& topLeft, int width, int height, const COLOR& color);

};

