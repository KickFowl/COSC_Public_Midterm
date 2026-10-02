#include "AnimationEngine.h"

AnimationEngine::AnimationEngine(WindowManager& window) : Graphics(window)
{

}

void AnimationEngine::tweenPolygons2D(polygon2D& start, polygon2D& end, tick begin, unsigned int length)
{
	polygon2D tweenedPoly;

	coord2D stepsOne = start.pos1.differance(end.pos1)/length;
	coord2D stepsTwo = start.pos2.differance(end.pos2)/length;
	coord2D stepsThree = start.pos3.differance(end.pos3)/length;

	tick currentStep = context.getTick() - begin;

	if (currentStep < length) {
		tweenedPoly = { start.pos1 * stepsOne * currentStep, start.pos2 * stepsTwo * currentStep, start.pos3 * stepsThree * currentStep };
	}
	else { tweenedPoly = end; }

	polygon2DRasterizer(tweenedPoly);
}
