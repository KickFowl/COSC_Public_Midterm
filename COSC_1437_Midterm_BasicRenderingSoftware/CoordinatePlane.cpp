#include "CoordinatePlane.h"

void CoordinatePlane::drawAxis(const COLOR& color)
{
	coord2D firstCoord = {origin.x, 0};
	coord2D secondCoord = {origin.x, (float)canvas.getHeight()};

	canvas.drawLine2D(firstCoord, secondCoord, color);
	
	firstCoord = { 0, origin.y };
	secondCoord = { (float)canvas.getWidth(), origin.y};
	
	canvas.drawLine2D(firstCoord, secondCoord, color);
}

CoordinatePlane::CoordinatePlane(Canvas& canvas, coord2D origin) : origin(origin), canvas(canvas)
{
}

void CoordinatePlane::drawCoordPlane(const COLOR& color)
{

	drawAxis(color);

}
