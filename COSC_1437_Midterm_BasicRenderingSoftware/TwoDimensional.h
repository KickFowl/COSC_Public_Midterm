#pragma once

#include "Canvas.h"
#include "dataStructs.h"
#include "DrawQueue.h"

class TwoDimensional
{

protected:

	Canvas& canvas;

public:

	TwoDimensional(Canvas& canvas) : canvas(canvas) {}

	void drawLine(const coord& pos1, const coord& pos2, const COLOR& color = colors::green);

	void drawPolygon(const polygon& poly, const COLOR& color = colors::green);

	void drawQuad(const quad& quad, const COLOR& color);

	void drawRect(const coord& start, int width, int height, const COLOR& color, alignment alightTo = alignment::TOPLEFT);


	void fillQuad(const quad& quad);
	void fillRect(const coord& topLeft, int width, int height, const COLOR& color);

};

