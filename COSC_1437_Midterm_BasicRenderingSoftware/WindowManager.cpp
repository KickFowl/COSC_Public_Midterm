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

void WindowManager::fillBitMap(const COLOR& color)
{
	int bitMapLength = WIDTH * HEIGHT;

	std::fill_n(&bitMap[0], bitMapLength, color.getColor_aRGB());
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

WindowManager::~WindowManager()
{
	if (bitMap) {
		VirtualFree(bitMap, 0, MEM_RELEASE);
	}
}
