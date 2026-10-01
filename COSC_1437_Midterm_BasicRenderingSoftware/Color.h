#pragma once
#include <Windows.h>
#include <cmath>
#include <stdint.h>
#include <algorithm>



class COLOR
{
	uint8_t alpha;
	uint8_t red;
	uint8_t green;
	uint8_t blue;

public:

	COLOR() = default;
	COLOR(uint32_t color);
	COLOR(uint8_t alpha, uint8_t red, uint8_t green, uint8_t blue);

	const uint32_t getColor_aRGB() { return (static_cast<uint32_t>(alpha) | static_cast<uint32_t>(red) | static_cast<uint32_t>(green) | static_cast<uint32_t>(blue)); };

	COLOR getGradiant_aRGB(COLOR& other, float t);

};


namespace colors {
	COLOR inline const green(0xFF, 0x00, 0xFF, 0x00);
}