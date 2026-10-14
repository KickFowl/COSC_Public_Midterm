#pragma once

#include <variant>
#include <vector>
#include <windows.h>
#include <windowsx.h>

#include "dataStructs.h"

struct dragStart
{
	int startX, startY;
};

struct dragEvent
{
	int startX, startY;
	int dx, dy;
};

struct dragEnd
{
	int startX, startY;
	int x, y;
};

using Event = std::variant<dragEvent, dragStart, dragEnd>;

class InputHandle
{

	std::vector<Event> eventQueue;

	bool isDragging = false;
	int startX = 0;
	int startY = 0;

public:

	void HandleKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam);
	void HandleMouseMove(UINT uMSG, WPARAM wParam, LPARAM lParam);

	void TranslateWin32Message(UINT uMsg, WPARAM wParam, LPARAM lParam);

	inline std::vector<Event> passEvents() { return std::move(eventQueue); }

};

