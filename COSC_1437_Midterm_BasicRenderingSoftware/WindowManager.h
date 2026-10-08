#pragma once
#include <windows.h>
#include <cstdint>
#include <cmath>
#include <stdint.h>
#include <queue>
#include <vector>
#include <algorithm>

#include "Color.h"
#include "dataStructs.h"

using tick = uint64_t;

class WindowManager
{
	int WIDTH;
	int HEIGHT;

	int bufferSize = WIDTH * HEIGHT * sizeof(uint32_t);

	tick mainTick;	
	uint64_t lastTick;

	uint64_t deltaTime;
	
	uint32_t* bitMap;
	BITMAPINFO* bufferBitMap;

	HWND windowHandle;
	bool isRunning;

	static bool const isClassRegistered = false;

	static LRESULT CALLBACK StaticWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT windowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	void updateTick();

public:
	WindowManager(BITMAPINFO* bitMap);
	WindowManager(BITMAPINFO* bitMap, int width, int height);

	const inline int getWidth() { return WIDTH; };
	const inline int getHeight() { return HEIGHT; };
	const inline tick getTick() { return mainTick; };

	void inline setBitMapAt(int x, int y, uint32_t color) { if (y <= HEIGHT) { bitMap[y * WIDTH + x] = color; }; };
	void inline setBitMapAt(const vertex& vert) { int index = int(vert.position.y * WIDTH + vert.position.x); if (index < bufferSize) bitMap[index] = vert.color.getColor_aRGB();};
	void inline setBitMapIndex(int index, uint32_t color) { if(index <= bufferSize) bitMap[index] = color; };
	void setBitMapSpan(span set);
	void fillBitMap(const COLOR& color);

	static void processMessages();

	bool createWindow(HINSTANCE hInstance, const wchar_t* title);

	void createBackBuffer();
	void swapBuffersToWindow();

	inline bool isWindowOpen() const { return isRunning; };

	tick getDeltaTime();


	~WindowManager();
};

