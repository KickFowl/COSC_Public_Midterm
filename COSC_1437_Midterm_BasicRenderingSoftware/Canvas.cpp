#include "Canvas.h"

bool Canvas::alongLine(coord insert, coord p1, coord p2)
{
	float m = p1.slope(p2);
	float b = m * p1.x - p1.y;

	if (insert.y == m * insert.x + b)
	{
		return true;
	}
	return false;
}

Canvas::Canvas(WindowManager& context) : context(context)
{}

void Canvas::setBackground(uint32_t color)
{
	backgroundColor = color;
}

void Canvas::setPixelColor(coord& pos, const COLOR& color)
{
	if (pos.x < 0 || pos.x >= context.getWidth() || pos.y < 0 || pos.y >= context.getHeight())
	{
		return;
	}

	context.setBitMapAt(pos.x, pos.y, color.getColor_aRGB());
}

void Canvas::draw()
{
	context.fillBitMap(backgroundColor);
	
	for(vertex cmd : drawQueue.drawQueue)
	{
			context.setBitMapAt(cmd);
	}

	drawQueue.clearQueue();
}