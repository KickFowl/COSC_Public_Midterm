#pragma once
#include <windows.h>
#include <cstdint>
#include <cmath>
#include <stdint.h>
#include <queue>
#include <cstdint>

#include "Color.h"

struct coord2D
{
	float x;
	float y;

	COLOR color = colors::green;

	coord2D operator + (coord2D& other) const
	{
		return coord2D{ x + other.x, y + other.y };
	}

	coord2D operator - (coord2D& other) const
	{
		return coord2D{ x - other.x, y - other.y };
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

class WindowManager
{
	int WIDTH;
	int HEIGHT;

	uint32_t backgroundColor;
	
	uint32_t* bitMap;
	BITMAPINFO* bufferBitMap;

	HWND windowHandle;
	bool isRunning;

	static bool const isClassRegistered = false;

	static LRESULT CALLBACK StaticWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT windowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	std::queue<coord2D> drawQueue2D;


public:

	WindowManager(BITMAPINFO* bitMap);
	WindowManager(BITMAPINFO* bitMap, int width, int height);

	static void processMessages();

	bool createWindow(HINSTANCE hInstance, const wchar_t* title);

	void createBackBuffer();
	void swapBuffersToWindow();

	inline bool isWindowOpen() const { return isRunning; };

	void setBackground(uint32_t color);

	void setPixelColor(coord2D pos);
	void drawLine2D(coord2D pos1, coord2D pos2);

	void draw2D();

	~WindowManager();
};

