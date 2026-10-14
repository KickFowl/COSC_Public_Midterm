#include "InputHandle.h"

void InputHandle::HandleKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    return;
};

void InputHandle::HandleMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    int mouseX = GET_X_LPARAM(lParam);
    int mouseY = GET_Y_LPARAM(lParam);

    switch (uMsg) {
    case WM_LBUTTONDOWN:
        isDragging = true;
        startX = mouseX;
        startY = mouseY;
        eventQueue.push_back(dragStart{ startX, startY });
        break;

    case WM_MOUSEMOVE:
        if (isDragging) {
            eventQueue.push_back(dragEvent{ startX, startY, mouseX, mouseY });
        }
        break;

    case WM_LBUTTONUP:
        if (isDragging) {
            isDragging = false;
            eventQueue.push_back(dragEnd{ startX, startY, mouseX, mouseY });
        }
        break;
    }
}

void InputHandle::TranslateWin32Message(UINT uMsg, WPARAM wParam, LPARAM lParam)
{

}
