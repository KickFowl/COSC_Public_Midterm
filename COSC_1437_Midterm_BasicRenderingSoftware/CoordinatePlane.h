#pragma once

#include "Canvas.h"
#include "Color.h"


class CoordinatePlane
{

	Canvas& canvas;
	coord2D origin;

	void drawAxis(const COLOR& color);

public:

	CoordinatePlane(Canvas& canvas, coord2D origin = {200, 200});

	void drawCoordPlane(const COLOR& color = colors::green);

};

