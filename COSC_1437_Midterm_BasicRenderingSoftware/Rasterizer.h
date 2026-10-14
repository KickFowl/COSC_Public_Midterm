#pragma once
#include "TwoDimensional.h"


class Rasterizer : protected TwoDimensional
{

	quad polygonBound(polygon& poly);
	quad ngonBound(ngon& non);

public:

	Rasterizer(Canvas& canvas) : TwoDimensional(canvas) {}

	void rasterizePolygon(const polygon& poly, const COLOR& color = colors::burgundy);
	rastPolyDebug rasterizeDebugPolygon(const polygon& poly, const COLOR& color = colors::burgundy);

};

