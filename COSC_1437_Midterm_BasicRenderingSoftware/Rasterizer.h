#pragma once
#include "TwoDimensional.h"


class Rasterizer : protected TwoDimensional
{

	quad2D polygonBound2D(polygon2D& poly);
	quad2D ngonBound2D(ngon2D& non);

public:

	Rasterizer(Canvas& canvas) : TwoDimensional(canvas) {}

	void rasterizePolygon(const polygon2D& poly, const COLOR& color = colors::burgundy, bool debug = false);

};

