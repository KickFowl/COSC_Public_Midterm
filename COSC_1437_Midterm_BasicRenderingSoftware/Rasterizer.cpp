#include "Rasterizer.h"

void Rasterizer::rasterizePolygon(const polygon& poly, const COLOR& color)
{
	const coord* orderedCoordsX[] = { &poly.pos1, &poly.pos2, &poly.pos3 };
	const coord* orderedCoordsY[] = { &poly.pos1, &poly.pos2, &poly.pos3 };

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

	const coord& a = *orderedCoordsX[0];

	const coord& top = (orderedCoordsX[1]->y >= orderedCoordsX[2]->y) ? *orderedCoordsX[1] : *orderedCoordsX[2];
	const coord& bottom = (orderedCoordsX[1]->y < orderedCoordsX[2]->y) ? *orderedCoordsX[1] : *orderedCoordsX[2];

	float slopeTop = a.slope(top);
	float slopeBottom = a.slope(bottom);
	float slopeOpposite = top.slope(bottom);

	float bTop = a.y - slopeTop * a.x;
	float bBottom = a.y - slopeBottom * a.x;
	float bOpposite = top.y - slopeOpposite * top.x;

	for (float y = orderedCoordsY[0]->y - 1; y < orderedCoordsY[2]->y + 1; y++)
	{
		for (float x = orderedCoordsX[0]->x; x < orderedCoordsX[2]->x + 1; x++)
		{
			if (y < slopeTop * x + bTop && y < slopeOpposite * x + bOpposite && y > slopeBottom * x + bBottom)
			{
				canvas.drawQueue.pushVert(coord{ x, y }, color);
			}
		}
	}

}

rastPolyDebug Rasterizer::rasterizeDebugPolygon(const polygon& poly, const COLOR& color)
{
	rastPolyDebug debugInfo;

	const coord* orderedCoordsX[] = { &poly.pos1, &poly.pos2, &poly.pos3 };

	float maxY = 0;
	float minY = canvas.getHeight();
	
	for (int i = 0; i < 2; i++)
	{
		if (orderedCoordsX[i]->x > orderedCoordsX[i + 1]->x)
		{
			std::swap(orderedCoordsX[i], orderedCoordsX[i + 1]);
			if (i == 1)
			{
				if (orderedCoordsX[i - 1]->x > orderedCoordsX[i]->x)
				{
					
					std::swap(orderedCoordsX[i - 1], orderedCoordsX[i]);
				}
			}
		}
	}

	for (const coord* pos : orderedCoordsX)
	{
		maxY = (maxY > pos->y) ? maxY : pos->y;
		minY = (minY < pos->y) ? minY : pos->y;
	}

	if (maxY > canvas.getHeight()) return debugInfo;

	if (orderedCoordsX[0]->x == orderedCoordsX[1]->x && orderedCoordsX[0]->y < orderedCoordsX[1]->y)
	{
		std::swap(orderedCoordsX[0], orderedCoordsX[1]);
	}

	debugInfo.boundingBox = quad{ {orderedCoordsX[0]->x, minY},{orderedCoordsX[2]->x, minY},{orderedCoordsX[2]->x, maxY},{orderedCoordsX[0]->x, maxY} };

	const coord* a = orderedCoordsX[0];
	const coord* top;
	const coord* bottom;

	//const coord* top = (orderedCoordsX[1]->y >= orderedCoordsX[2]->y) ? orderedCoordsX[1] : orderedCoordsX[2];
	//const coord* bottom = (orderedCoordsX[1]->y < orderedCoordsX[2]->y) ? orderedCoordsX[1] : orderedCoordsX[2];

	float testSlope = a->slope(*orderedCoordsX[1]);
	float testB = a->y - testSlope * a->x;

	if (orderedCoordsX[2]->y > testSlope * orderedCoordsX[2]->x + testB)
	{
		top = orderedCoordsX[2];
		bottom = orderedCoordsX[1];
	}
	else
	{
		top = orderedCoordsX[1];
		bottom = orderedCoordsX[2];
	}

	float slopeTop = a->slope(*top);
	float slopeBottom = a->slope(*bottom);
	float slopeOpposite = top->slope(*bottom);

	float bTop = a->y - slopeTop * a->x;
	float bBottom = a->y - slopeBottom * a->x;
	float bOpposite = top->y - slopeOpposite * top->x;

	for (float y = minY - 1; y < maxY + 1; y++)
	{
		for (float x = orderedCoordsX[0]->x; x < orderedCoordsX[2]->x + 1; x++)
		{
			if ((y < slopeTop * x + bTop && y > slopeBottom * x + bBottom) || (top->x == a->x && y > slopeBottom * x + bBottom) || (bottom->x == a->x && y < slopeTop * x + bTop))
			{
				if ((y > slopeOpposite * x + bOpposite && top->x > bottom->x) || (y < slopeOpposite * x + bOpposite && top->x <= bottom->x)) canvas.drawQueue.pushVert(coord{ x, y }, color);
			}
		}
	}

	debugInfo.a = *a;
	debugInfo.top = *top;
	debugInfo.bottom = *bottom;

	return debugInfo;
}
