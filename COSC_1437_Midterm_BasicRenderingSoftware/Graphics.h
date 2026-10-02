#pragma once

#include "WindowManager.h"
#include <array>
#include <vector>

enum alignment {
	TOPLEFT,
	TOPRIGHT,
	BOTTOMLEFT,
	BOTTOMRIGHT,
	CENTER
};

struct coord2D
{
	float x;
	float y;

	COLOR color = colors::burgundy;

	coord2D operator + (coord2D& other) const { return coord2D{ x + other.x, y + other.y }; }
	coord2D operator - (coord2D& other) const { return coord2D{ x - other.x, y - other.y }; }
	
	coord2D operator/(unsigned int divisor) { return coord2D{ x / divisor, y / divisor}; }
	coord2D operator/(int divisor) { return coord2D{ x / divisor, y / divisor }; }
	coord2D operator/(float divisor) { return coord2D{ x / divisor, y / divisor }; }
	coord2D operator/(coord2D& divisor)	{ return coord2D{ x / divisor.x, y / divisor.y };}

	coord2D operator*(unsigned int divisor) { return coord2D{ x * divisor, y * divisor }; }
	coord2D operator*(int divisor) { return coord2D{ x * divisor, y * divisor }; }
	coord2D operator*(float divisor) { return coord2D{ x * divisor, y * divisor }; }
	coord2D operator*(tick divisor) { return coord2D{ x * divisor, y * divisor }; }
	coord2D operator*(coord2D& divisor) { return coord2D{ x * divisor.x, y * divisor.y }; }
	
	coord2D differance(coord2D& other){
		return coord2D{
			x - other.x,
			y - other.y
		};
	}
	float slope(coord2D& other)
	{
		return (y - other.y) / (x - other.x);
	}
};

struct coord3D
{
	float x;
	float y;
	float z;

	COLOR color = colors::green;

	coord3D operator+(coord3D& other)
	{
		return coord3D{ x + other.x, y + other.y, z + other.z };
	}
	coord3D operator-(coord3D& other)
	{
		return coord3D{ x - other.x, y - other.y, z - other.z };
	}
};

struct polygon2D
{
	coord2D pos1, pos2, pos3;
};

struct quad2D
{
	coord2D pos1, pos2, pos3, pos4;
};

struct nongon2D
{
	std::vector<coord2D> coords;
};

class Graphics
{
	uint32_t backgroundColor;

	std::vector<coord2D> drawQueue2D;

protected:
	WindowManager& context;

	std::array<coord2D, 3> polygonSortX(polygon2D& poly);
	std::array<coord2D, 3> polygonSortY(polygon2D& poly);

	bool alongLine(coord2D insert, coord2D p1, coord2D p2);

	quad2D polygonBound2D(polygon2D& poly);
	quad2D nongonBound2D(nongon2D& non);

	void inline setContext(WindowManager& newContext) { context = newContext; };
public:
	Graphics(WindowManager& context);

	const inline WindowManager& getContext() { return context; };

	void setBackground(uint32_t color);
	void setPixelColor(coord2D& pos);

	void drawLine2D(coord2D& pos1, coord2D& pos2);
	void drawLine2D(coord2D& pos1, coord2D& pos2, const COLOR& color);

	void drawPolygon2D(polygon2D& poly);
	void fanFillPolygon2D(polygon2D& poly);
	void polygon2DRasterizer(polygon2D& poly, bool debug = false);

	void drawQuad2D(quad2D& quad);

	void drawRect2D(coord2D& start, int width, int height, alignment alignTo = TOPLEFT);
	void drawRect2D(coord2D& start, int width, int height, const COLOR& color, alignment alightTo = TOPLEFT);


	void fillQuad2D(quad2D& quad);
	void fillRect2D(coord2D& topLeft, int width, int height);

	void draw2D();

};

