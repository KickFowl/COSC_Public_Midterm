#include "TwoDimensional.h"

void TwoDimensional::drawLine(const coord& pos1,const coord& pos2, const COLOR& color)
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

	while (true) {

		canvas.drawQueue.pushVert(vertex{ color, coord{ x1, y1 } });

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

void TwoDimensional::drawPolygon(const polygon& poly, const COLOR& color)
{
	drawLine(poly.pos1, poly.pos2, color);
	drawLine(poly.pos1, poly.pos3, color);
	drawLine(poly.pos3, poly.pos2, color);
}

void TwoDimensional::drawQuad(const quad& quad, const COLOR& color)
{
	drawLine(quad.pos1, quad.pos2, color);
	drawLine(quad.pos2, quad.pos3, color);
	drawLine(quad.pos3, quad.pos4, color);
	drawLine(quad.pos4, quad.pos1, color);
}

void TwoDimensional::drawRect(const coord& start, int width, int height, const COLOR& color, alignment alignTo)
{
	coord topLeft;

	switch (alignTo)
	{
	case alignment::TOPLEFT:
		topLeft = start;
		break;
	case alignment::TOPRIGHT:
		topLeft = coord{ start.x - width, start.y };
		break;
	case alignment::BOTTOMRIGHT:
		topLeft = coord{ start.x - width, start.y - height };
		break;
	case alignment::BOTTOMLEFT:
		topLeft = coord{ start.x, start.y - height };
		break;
	case alignment::CENTER:
		topLeft = coord{ start.x - 0.5f * width, start.y - 0.5f * height };
		break;
	}
	coord topRight = { topLeft.x + width, topLeft.y};
	coord bottomLeft = { topLeft.x , topLeft.y + height};
	coord bottomRight = { topLeft.x + width, topLeft.y + height};

	drawLine(topLeft, topRight, color);
	drawLine(topRight, bottomRight, color);
	drawLine(bottomRight, bottomLeft, color);
	drawLine(bottomLeft, topLeft, color);
}

void TwoDimensional::fillRect(const coord& topLeft, int width, int height, const COLOR& color)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		canvas.drawQueue.pushVert(coord{ topLeft.x + j, topLeft.y + i }, color);
	}
}

