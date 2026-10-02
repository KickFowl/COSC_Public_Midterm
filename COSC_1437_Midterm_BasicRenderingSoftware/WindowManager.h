#pragma once
#include <windows.h>
#include <cstdint>
#include <cmath>
#include <stdint.h>
#include <queue>
#include <cstdint>
#include <vector>

#include "Color.h"

using tick = uint64_t;

class WindowManager
{
	int WIDTH;
	int HEIGHT;

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

	void inline setBitMapAt(int x, int y, uint32_t color) { bitMap[y * WIDTH + x] = color; };
	void inline setBitMapIndex(int index, uint32_t color) { bitMap[index] = color; };

	static void processMessages();

	bool createWindow(HINSTANCE hInstance, const wchar_t* title);

	void createBackBuffer();
	void swapBuffersToWindow();

	inline bool isWindowOpen() const { return isRunning; };

	tick getDeltaTime();


	~WindowManager();
};

