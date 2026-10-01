#include "WindowManager.h"

LRESULT WindowManager::StaticWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	WindowManager * manager = nullptr;

	if (uMsg == WM_NCCREATE) {
		CREATESTRUCT* pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
		manager = reinterpret_cast<WindowManager*>(pCreate->lpCreateParams);

		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)manager);
	}
	else
	{
		manager = reinterpret_cast<WindowManager*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
	}

	if (manager)
	{
		return manager->windowProc(hwnd, uMsg, wParam, lParam);
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

LRESULT WindowManager::windowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_DESTROY:
		isRunning = false;
		PostQuitMessage(0);
		return 0;

	case WM_SIZE:
		// Optional: Update WIDTH and HEIGHT here, then call createBackBuffer() 
		// to dynamically resize your rendering target when the user scales the window.
		WIDTH = LOWORD(lParam);
		HEIGHT = HIWORD(lParam);

		createBackBuffer();
		return 0;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

WindowManager::WindowManager(BITMAPINFO * bitMap) : WIDTH(200), HEIGHT(200), bufferBitMap(bitMap)
{
	
}

WindowManager::WindowManager(BITMAPINFO* bitMap, int width, int height) : WIDTH(width), HEIGHT(height), bufferBitMap(bitMap)
{

}

void WindowManager::processMessages()
{
	MSG msg = {};
	// Passing nullptr for HWND grabs messages for ALL windows on this thread
	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg); // This automatically routes to the correct window's StaticWindowProc
	}
}

bool WindowManager::createWindow(HINSTANCE hInstance, const wchar_t* title)
{
	WNDCLASS wc = {};
	wc.lpfnWndProc = StaticWindowProc; // Attach the static router
	wc.hInstance = hInstance;
	wc.lpszClassName = L"MyWindowClass";

	RegisterClass(&wc);

	windowHandle = CreateWindowEx(
		0, L"MyWindowClass", title,
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		CW_USEDEFAULT, CW_USEDEFAULT, WIDTH, HEIGHT,
		NULL, NULL, hInstance,
		this // CRITICAL: Pass the instance pointer into the window creation
	);

	if (!windowHandle) return false;

	isRunning = true;
	createBackBuffer(); // Automatically size the backbuffer
	return true;
}

void WindowManager::createBackBuffer()
{
	if (bitMap) {
		VirtualFree(bitMap, 0, MEM_RELEASE);
		bitMap = nullptr;
	}

	bufferBitMap->bmiHeader.biSize = sizeof(bufferBitMap->bmiHeader);
	bufferBitMap->bmiHeader.biWidth = WIDTH;
	bufferBitMap->bmiHeader.biHeight = -HEIGHT;
	bufferBitMap->bmiHeader.biPlanes = 1;
	bufferBitMap->bmiHeader.biBitCount = 32;
	bufferBitMap->bmiHeader.biCompression = BI_RGB;

	int bufferMemorySize = WIDTH * HEIGHT * sizeof(uint32_t);
	bitMap = (uint32_t*)VirtualAlloc(0, bufferMemorySize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
}

void WindowManager::swapBuffersToWindow()
{
	if (!bitMap || !windowHandle) return;

	HDC deviceContext = GetDC(windowHandle);

	StretchDIBits(

		deviceContext,
		0, 0, WIDTH, HEIGHT,
		0, 0, WIDTH, HEIGHT,
		bitMap,
		bufferBitMap,
		DIB_RGB_COLORS, SRCCOPY

	);

	ReleaseDC(windowHandle, deviceContext);
}

void WindowManager::setBackground(uint32_t color)
{
	backgroundColor = color;
}

void WindowManager::setPixelColor(coord2D pos)
{
	if (pos.x < 0 || pos.x >= WIDTH || pos.y < 0 || pos.y >= HEIGHT)
	{
		return;
	}

	bitMap[int(pos.y * WIDTH + pos.x)] = pos.color.getColor_aRGB();
}

void WindowManager::drawLine2D(coord2D pos1, coord2D pos2)
{
	float x1 = pos1.x;
	float y1 = pos1.y;
	float x2 = pos2.x;
	float y2 = pos2.y;

	// Calculate absolute differences and step directions
	int dx = abs(x2 - x1);
	int sx = (x1 < x2) ? 1 : -1;

	int dy = -abs(y2 - y1);
	int sy = (y1 < y2) ? 1 : -1;

	// The error accumulator keeps track of when we need to step diagonally
	int error = dx + dy;

	// A simple while loop replaces your recursive marchingLineLoop
	while (true) {
		drawQueue2D.push(coord2D{ x1, y1, pos1.color.getColor_aRGB() });

		// Stop when we reach the end coordinate
		if (x1 == x2 && y1 == y2) {
			break;
		}

		int e2 = 2 * error;

		// Step horizontally if needed
		if (e2 >= dy) {
			error += dy;
			x1 += sx;
		}
		// Step vertically if needed
		if (e2 <= dx) {
			error += dx;
			y1 += sy;
		}
	}
}

void WindowManager::draw2D()
{
	for (int i = 0; i < WIDTH * HEIGHT; i++)
	{
		bitMap[i] = backgroundColor;
	}
	while (!drawQueue2D.empty())
	{
		setPixelColor(drawQueue2D.front());
		drawQueue2D.pop();
	}
}

WindowManager::~WindowManager()
{
	if (bitMap) {
		VirtualFree(bitMap, 0, MEM_RELEASE);
	}
}
