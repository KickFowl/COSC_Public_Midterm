#pragma once
#include <windows.h>
#include <d3d11.h>
#include <cstdint>
#include <cmath>
#include <stdint.h>

struct coord
{
	int x;
	int y;

	coord operator + (coord& other) const
	{
		return coord{ x + other.x, y + other.y };
	}

	coord operator - (coord& other) const
	{
		return coord{ x - other.x, y - other.y };
	}
};

class WindowManager
{
	int WIDTH;
	int HEIGHT;
	
	uint32_t* bitMap;
	BITMAPINFO* bufferBitMap;

	HWND windowHandle;
	bool isRunning;

	static bool const isClassRegistered = false;

	static LRESULT CALLBACK StaticWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT windowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
public:

	WindowManager(BITMAPINFO* bitMap);
	WindowManager(BITMAPINFO* bitMap, int width, int height);

	static void processMessages();

	bool createWindow(HINSTANCE hInstance, const wchar_t* title);

	void createBackBuffer();
	void swapBuffersToWindow();

	inline bool isWindowOpen() const { return isRunning; };

	void fillBackground(uint32_t color);

	void setPixelColor(coord pos, uint32_t color);
	void drawLine(coord pos1, coord pos2, uint32_t color);

	~WindowManager();
};

