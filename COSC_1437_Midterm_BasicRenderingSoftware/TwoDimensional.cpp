#include "TwoDimensional.h"

void TwoDimensional::drawLine(coord2D& pos1, coord2D& pos2, const COLOR& color)
{
	float x1 = pos1.x;
	float y1 = pos1.y;
	float x2 = pos2.x;
	float y2 = pos2.y;

	// Calculate absolute differences and step directions
	int dx = abs(x2 - x1);
	int sx = (x1 < x2) ? 1 : -1;

	int dy = -abs(y2 - y1);
	int sy = (y1 < y2) ? 1 : -1;

	// The error accumulator keeps track of when we need to step diagonally
	int error = dx + dy;

	if (dy == 0)
	{
		canvas.drawQueue.pushSpan({x1, y1}, int(x2 - x1), color);
		return;
	}

	while (true) {

		canvas.drawQueue.pushVert(vertex{ color, coord2D{ x1, y1 } });

		if (x1 == x2 && y1 == y2)
		{
			break;	
		}

		int e2 = 2 * error;
		
		if (e2 <= dx) {
			error += dx;
			y1 += sy;
		}
		if (e2 >= dy) {
			error += dy;
			x1 += sx;
		}
	}
}

void TwoDimensional::drawPolygon(polygon2D& poly, const COLOR& color)
{
	drawLine(poly.pos1, poly.pos2, color);
	drawLine(poly.pos1, poly.pos3, color);
	drawLine(poly.pos3, poly.pos2, color);
}

void TwoDimensional::drawQuad(quad2D& quad, const COLOR& color)
{
	drawLine(quad.pos1, quad.pos2, color);
	drawLine(quad.pos2, quad.pos3, color);
	drawLine(quad.pos3, quad.pos4, color);
	drawLine(quad.pos4, quad.pos1, color);
}

void TwoDimensional::drawRect(coord2D& start, int width, int height, const COLOR& color, alignment alignTo)
{
	coord2D topLeft;

	switch (alignTo)
	{
	case alignment::TOPLEFT:
		topLeft = start;
		break;
	case alignment::TOPRIGHT:
		topLeft = coord2D{ start.x - width, start.y };
		break;
	case alignment::BOTTOMRIGHT:
		topLeft = coord2D{ start.x - width, start.y - height };
		break;
	case alignment::BOTTOMLEFT:
		topLeft = coord2D{ start.x, start.y - height };
		break;
	case alignment::CENTER:
		topLeft = coord2D{ start.x - 0.5f * width, start.y - 0.5f * height };
		break;
	}
	coord2D topRight = { topLeft.x + width, topLeft.y};
	coord2D bottomLeft = { topLeft.x , topLeft.y + height};
	coord2D bottomRight = { topLeft.x + width, topLeft.y + height};

	drawLine(topLeft, topRight, color);
	drawLine(topRight, bottomRight, color);
	drawLine(bottomRight, bottomLeft, color);
	drawLine(bottomLeft, topLeft, color);
}

void TwoDimensional::fillRect(coord2D& topLeft, int width, int height, const COLOR& color)
{
	for (int i = 0; i < height; i++)
	{
		canvas.drawQueue.pushSpan(coord2D{ topLeft.x, topLeft.y + i }, width, color);
	}
}

