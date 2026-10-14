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
#include "InputHandle.h"

class WindowManager
{
	int WIDTH;
	int HEIGHT;

	int bufferSize = WIDTH * HEIGHT * sizeof(uint32_t);
	
	uint32_t* bitMap;
	BITMAPINFO* bufferBitMap;

	HWND windowHandle;
	bool isRunning;

	static bool const isClassRegistered = false;

	static LRESULT CALLBACK StaticWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT windowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	InputHandle* inputHandler = nullptr;

public:
	WindowManager(BITMAPINFO* bitMap);
	WindowManager(BITMAPINFO* bitMap, int width, int height);

	const inline int getWidth() { return WIDTH; };
	const inline int getHeight() { return HEIGHT; };

	inline void setInputHandler(InputHandle* h) { inputHandler = h; }

	void inline setBitMapAt(int x, int y, uint32_t color) { if (y <= HEIGHT) { bitMap[y * WIDTH + x] = color; }; };
	void inline setBitMapAt(const vertex& vert) { int index = int(vert.position.y * WIDTH + vert.position.x); if (index < WIDTH * HEIGHT) bitMap[index] = vert.color.getColor_aRGB(); };
	void inline setBitMapIndex(int index, uint32_t color) { if(index <= bufferSize) bitMap[index] = color; };
	void fillBitMap(const COLOR& color);

	static void processMessages();

	bool createWindow(HINSTANCE hInstance, const wchar_t* title);

	void createBackBuffer();
	void swapBuffersToWindow();

	inline bool isWindowOpen() const { return isRunning; };


	~WindowManager();
};

