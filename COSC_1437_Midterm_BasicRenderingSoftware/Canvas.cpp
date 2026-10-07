#include "Canvas.h"

bool Canvas::alongLine(coord2D insert, coord2D p1, coord2D p2)
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

void Canvas::setPixelColor(coord2D& pos, COLOR& color)
{
	if (pos.x < 0 || pos.x >= context.getWidth() || pos.y < 0 || pos.y >= context.getHeight())
	{
		return;
	}

	context.setBitMapAt(pos.x, pos.y, color.getColor_aRGB());
}

void Canvas::drawLine2D(coord2D& pos1, coord2D& pos2)
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
		drawQueue2D.push_back(coord2D{ x1, y1, pos1.color.getColor_aRGB() });

		// Stop when we reach the end coordinate
		if (x1 == x2 && y1 == y2) {
			break;
		}

		int e2 = 2 * error;

		// Step horizontally if needed
		if (e2 >= dy) {
			error += dy;
			x1 += sx;
		}
		// Step vertically if needed
		if (e2 <= dx) {
			error += dx;
			y1 += sy;
		}
	}
}

void Canvas::drawLine2D(coord2D& pos1, coord2D& pos2, const COLOR& color)
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
		coord2D newPos{x1, y1, color};

		drawQueue2D.push_back(newPos);

		// Stop when we reach the end coordinate
		if (x1 == x2 && y1 == y2) {
			break;
		}

		int e2 = 2 * error;

		// Step horizontally if needed
		if (e2 >= dy) {
			error += dy;
			x1 += sx;
		}
		// Step vertically if needed
		if (e2 <= dx) {
			error += dx;
			y1 += sy;
		}
	}
}

void Canvas::drawPolygon2D(polygon2D& poly)
{
	drawLine2D(poly.pos1, poly.pos2);
	drawLine2D(poly.pos1, poly.pos3);
	drawLine2D(poly.pos3, poly.pos2);
}

void Canvas::fanFillPolygon2D(polygon2D& poly)
{
	coord2D constent = poly.pos1;

	coord2D start = poly.pos2;
	coord2D end = poly.pos3;


	float x1 = start.x;
	float y1 = start.y;
	float x2 = end.x;
	float y2 = end.y;

	// Calculate absolute differences and step directions
	int dx = abs(x2 - x1);
	int sx = (x1 < x2) ? 1 : -1;

	int dy = -abs(y2 - y1);
	int sy = (y1 < y2) ? 1 : -1;

	// The error accumulator keeps track of when we need to step diagonally
	int error = dx + dy;

	while (true) {
		coord2D secondCoord = coord2D{ x1, y1 };
		drawLine2D(constent, secondCoord);

		// Stop when we reach the end coordinate
		if (x1 == x2 && y1 == y2) {
			break;
		}

		int e2 = 2 * error;

		// Step horizontally if needed
		if (e2 >= dy) {
			error += dy;
			x1 += sx;
		}
		// Step vertically if needed
		if (e2 <= dx) {
			error += dx;
			y1 += sy;
		}
	}
}

void Canvas::polygon2DRasterizer(polygon2D& poly, bool debug)
{

}

void Canvas::drawQuad2D(quad2D& quad)
{
	drawLine2D(quad.pos1, quad.pos2);
	drawLine2D(quad.pos2, quad.pos3);
	drawLine2D(quad.pos3, quad.pos4);
	drawLine2D(quad.pos4, quad.pos1);
}

void Canvas::drawRect2D(coord2D& start, int width, int height, alignment alignTo)
{
	coord2D topLeft;

	switch (alignTo)
	{
	case TOPLEFT:
		topLeft = start;
		break;
	case TOPRIGHT:
		topLeft = coord2D{ start.x - width, start.y };
		break;
	case BOTTOMRIGHT:
		topLeft = coord2D{ start.x - width, start.y - height };
		break;
	case BOTTOMLEFT:
		topLeft = coord2D{ start.x, start.y - height };
		break;
	case CENTER:
		topLeft = coord2D{ start.x - 0.5f * width, start.y - 0.5f * height };
		break;
	}
	coord2D topRight = { topLeft.x + width, topLeft.y, topLeft.color };
	coord2D bottomLeft = { topLeft.x , topLeft.y + height, topLeft.color };
	coord2D bottomRight = { topLeft.x + width, topLeft.y + height, topLeft.color };

	drawLine2D(topLeft, topRight);
	drawLine2D(topRight, bottomRight);
	drawLine2D(bottomRight, bottomLeft);
	drawLine2D(bottomLeft, topLeft);
}

void Canvas::drawRect2D(coord2D& start, int width, int height, const COLOR& color, alignment alignTo)
{
	coord2D topLeft;

	switch (alignTo)
	{
	case TOPLEFT:
		topLeft = start;
		break;
	case TOPRIGHT:
		topLeft = coord2D{start.x - width, start.y};
		break;
	case BOTTOMRIGHT:
		topLeft = coord2D{start.x - width, start.y - height};
		break;
	case BOTTOMLEFT:
		topLeft = coord2D{start.x, start.y - height};
		break;
	case CENTER:
		topLeft = coord2D{start.x - 0.5f * width, start.y - 0.5f * height};
		break;
	}
	
	topLeft.color = color;
	
	coord2D topRight = { topLeft.x + width, topLeft.y, topLeft.color };
	coord2D bottomLeft = { topLeft.x , topLeft.y + height, topLeft.color };
	coord2D bottomRight = { topLeft.x + width, topLeft.y + height, topLeft.color };

	drawLine2D(topLeft, topRight);
	drawLine2D(topRight, bottomRight);
	drawLine2D(bottomRight, bottomLeft);
	drawLine2D(bottomLeft, topLeft);
}

void Canvas::fillQuad2D(quad2D& quad)
{

}

void Canvas::fillRect2D(coord2D& topLeft, int width, int height)
{

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			drawQueue2D.push_back(coord2D{ j + topLeft.x, i + topLeft.y });
		}
	}

}

void Canvas::draw2D()
{
	for (int i = 0; i < context.getWidth() * context.getHeight(); i++)
	{
		context.setBitMapIndex(i, backgroundColor);
	}
	for (auto& pixel : drawQueue2D)
	{
		setPixelColor(pixel);
	}
	drawQueue2D.clear();
}