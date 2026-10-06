#pragma once
#include "Canvas.h"


class Rasterizer
{

	Canvas& canvas;

public:

	void rasterizePolygon(const polygon2D& poly);

};

