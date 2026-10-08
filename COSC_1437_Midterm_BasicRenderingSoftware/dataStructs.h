#pragma once

#include "Color.h"

enum class alignment {
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

	coord2D operator + (const coord2D& other) const { return coord2D{ x + other.x, y + other.y }; }
	coord2D operator - (const coord2D& other) const { return coord2D{ x - other.x, y - other.y }; }

	coord2D operator/(float divisor) { return coord2D{ x / divisor, y / divisor }; }
	coord2D operator/(const coord2D& divisor) { return coord2D{ x / divisor.x, y / divisor.y }; }

	coord2D operator*(float factor) { return coord2D{ x * factor, y * factor }; }
	coord2D operator*(const coord2D& factor) { return coord2D{ x * factor.x, y * factor.y }; }

	coord2D differance(coord2D& other) {
		return coord2D{
			x - other.x,
			y - other.y
		};
	}
	float slope(const coord2D& other)
	{
		if (x - other.x == 0) return -1.0;
		return (y - other.y) / (x - other.x);
	}
};

struct coord3D
{
	float x;
	float y;
	float z;

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

struct ngon2D
{
	std::vector<coord2D> coords;
};

struct span
{
	const COLOR& color;
	coord2D start;
	int length, z_index;

	void operator=(span other)
	{
		start = other.start;
		length = other.length;
		z_index = other.z_index;
	}
};