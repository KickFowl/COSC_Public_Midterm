#include "Color.h"

COLOR::COLOR(uint32_t color) : alpha( color >> 24), red(color >> 16), green(color >> 8), blue(color)
{
}

COLOR::COLOR(uint8_t alpha, uint8_t red, uint8_t green, uint8_t blue) : alpha(alpha), red(red), green(green), blue(blue)
{}

COLOR COLOR::getGradiant_aRGB(COLOR& other, float t)
{
	t = std::clamp(t, 0.0f, 1.0f);

	uint8_t endA = (other.getColor_aRGB() >> 24) & 0xFF;
	uint8_t endR = (other.getColor_aRGB() >> 16) & 0xFF;
	uint8_t endG = (other.getColor_aRGB() >> 8) & 0xFF;
	uint8_t endB = other.getColor_aRGB() & 0xFF;

	COLOR newColor(
		static_cast<uint8_t>(std::round((1.0f - t) * alpha + t * endA)),
		static_cast<uint8_t>(std::round((1.0f - t) * red + t * endR)),
		static_cast<uint8_t>(std::round((1.0f - t) * green + t * endG)),
		static_cast<uint8_t>(std::round((1.0f - t) * blue + t * endB))
	);

	return newColor;
}
