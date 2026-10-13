#pragma once

#include "Color.h"

enum class alignment {
	TOPLEFT,
	TOPRIGHT,
	BOTTOMLEFT,
	BOTTOMRIGHT,
	CENTER
};

struct coord
{
	float x;
	float y;
	float z;

	coord operator + (const coord& other) const { return coord{ x + other.x, y + other.y }; }
	coord operator - (const coord& other) const { return coord{ x - other.x, y - other.y }; }

	coord operator/(float divisor) { return coord{ x / divisor, y / divisor }; }
	coord operator/(const coord& divisor) { return coord{ x / divisor.x, y / divisor.y }; }

	coord operator*(float factor) { return coord{ x * factor, y * factor }; }
	coord operator*(const coord& factor) { return coord{ x * factor.x, y * factor.y }; }

	coord differance(coord& other) {
		return coord{
			x - other.x,
			y - other.y
		};
	}
	float slope(const coord& other) const
	{
		if (x - other.x == 0) return -1.0;
		return (y - other.y) / (x - other.x);
	}
	float lastBytePosition()
	{
		return x * y;
	}
};

struct polygon
{
	coord pos1, pos2, pos3;
};

struct quad
{
	coord pos1, pos2, pos3, pos4;
};

struct ngon
{
	std::vector<coord> coords;
};

struct vertex
{
	const COLOR& color;
	coord position;
	int z_index;
};