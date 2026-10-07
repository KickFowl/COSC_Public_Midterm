#pragma once
#include "TwoDimensional.h"


class Rasterizer : public TwoDimensional
{

	Canvas& canvas;

	quad2D polygonBound2D(polygon2D& poly);
	quad2D ngonBound2D(ngon2D& non);

public:

	Rasterizer(Canvas& canvas) : canvas(canvas) {}

	void rasterizePolygon(const polygon2D& poly);

};

