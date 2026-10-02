#pragma once

#include "Graphics.h"

class AnimationEngine : public Graphics
{


public:
	AnimationEngine(WindowManager& window);


	void tweenPolygons2D(polygon2D& start, polygon2D& end, tick begin, unsigned int length);

};

