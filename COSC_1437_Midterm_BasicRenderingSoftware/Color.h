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

	const uint32_t getColor_aRGB() { return (static_cast<uint32_t>(alpha) << 24 | static_cast<uint32_t>(red) << 16 | static_cast<uint32_t>(green) << 8 | static_cast<uint32_t>(blue)); };

	COLOR getGradiant_aRGB(COLOR& other, float t);

};


namespace colors {
	COLOR inline const green(0xFF00FF00);
	COLOR inline const blue(0xFF0000FF);
	COLOR inline const red(0xFFFF0000);
	COLOR inline const yellow(0xFFFFFF00);
	COLOR inline const megenta(0xFFFF00FF);
	COLOR inline const cyan(0xFF00FFFF);
	
	COLOR inline const burgundy(0xFF660033);
}