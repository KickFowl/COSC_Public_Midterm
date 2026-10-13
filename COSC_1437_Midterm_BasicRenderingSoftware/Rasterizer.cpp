#include "Rasterizer.h"

void Rasterizer::rasterizePolygon(const polygon2D& poly, const COLOR& color, bool debug)
{

	const coord2D* orderedCoordsX[] = { &poly.pos1, &poly.pos2, &poly.pos3 };
	const coord2D* orderedCoordsY[] = { &poly.pos1, &poly.pos2, &poly.pos3 };

	for (int i = 0; i < 2; i++)
	{
		if (orderedCoordsX[i]->x > orderedCoordsX[i + 1]->x)
		{
			std::swap(orderedCoordsX[i], orderedCoordsX[i + 1]);
			if (i - 1 >= 0)
			{
				if (orderedCoordsX[i - 1]->x > orderedCoordsX[i]->x)
				{
					std::swap(orderedCoordsX[i - 1], orderedCoordsX[i]);
				}
			}
		}
		if (orderedCoordsY[i]->y > orderedCoordsY[i + 1]->y)
		{
			std::swap(orderedCoordsY[i], orderedCoordsY[i + 1]);
			if (i - 1 >= 0)
			{
				if (orderedCoordsY[i - 1]->y > orderedCoordsY[i]->y)
				{
					std::swap(orderedCoordsY[i - 1], orderedCoordsY[i]);
				}
			}
		}
	}

	if (orderedCoordsY[0]->y > canvas.getHeight()) return;

	if (orderedCoordsX[0]->x == orderedCoordsX[1]->x && orderedCoordsX[0]->y < orderedCoordsX[1]->y)
	{
		std::swap(orderedCoordsX[0], orderedCoordsX[1]);
	}


	if (debug)
	{
		coord2D topLeft{ orderedCoordsX[0]->x, orderedCoordsY[0]->y };
		drawRect(topLeft, orderedCoordsX[2]->x + 1 - orderedCoordsX[0]->x, orderedCoordsY[2]->y + 1 - orderedCoordsY[0]->y, colors::green);
	}

	const coord2D& a = *orderedCoordsX[0];

	const coord2D& top = (orderedCoordsX[1]->y >= orderedCoordsX[2]->y) ? *orderedCoordsX[1] : *orderedCoordsX[2];
	const coord2D& bottom = (orderedCoordsX[1]->y < orderedCoordsX[2]->y) ? *orderedCoordsX[1] : *orderedCoordsX[2];

	float slopeTop = a.slope(top);
	float slopeBottom = a.slope(bottom);
	float slopeOpposite = top.slope(bottom);

	float bTop = a.y - slopeTop * a.x;
	float bBottom = a.y - slopeBottom * a.x;
	float bOpposite = top.y - slopeOpposite * top.x;

	span newSpan = { color, {0, 0}, 0 };

	for (float y = orderedCoordsY[0]->y - 1; y < orderedCoordsY[2]->y + 1; y++)
	{
		bool noStart = true;
		for (float x = orderedCoordsX[0]->x; x < orderedCoordsX[2]->x + 1; x++)
		{
			if (y < slopeTop * x + bTop && y < slopeOpposite * x + bOpposite && y > slopeBottom * x + bBottom)
			{
				if (noStart)
				{
					newSpan.start = { x, y };
					noStart = false;
				}
				if (!noStart) newSpan.length++;
			}
		}
		if(newSpan.length != 0)	canvas.drawQueue.pushSpan(newSpan);
		newSpan.length = 0;
	}

	if (debug)
	{
		drawLine(a, top, colors::red);
		drawLine(a, bottom, colors::green);
		drawLine(top, bottom, colors::blue);

		drawRect(a, 10, 10, colors::red, alignment::CENTER);
		drawRect(top, 10, 10, colors::green, alignment::CENTER);
		drawRect(bottom, 10, 10, colors::blue, alignment::CENTER);
	}

}
