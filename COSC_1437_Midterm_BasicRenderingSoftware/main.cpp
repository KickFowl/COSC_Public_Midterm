#include <cmath>

#include "WindowManager.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    BITMAPINFO bitmapInfo = {};

    // Instantiate your class
    WindowManager window(&bitmapInfo, 800, 600);

    // Create the window
    if (!window.createWindow(hInstance, L"Software Renderer")) {
        return 0;
    }

    float angle = 1;
    float radius = 50;
    float conversion = 3.14 / 180;
    coord center = { 200, 200 };

    while (window.isWindowOpen())
    {
        WindowManager::processMessages();
        window.fillBackground(0xFF000010);

        window.drawLine(coord{ int(cos(angle) * radius) + center.x, int(sin(angle) * radius) + center.y }, coord{ int(cos(angle) * -radius) + center.x, int(sin(angle) * -radius) + center.y }, 0xFF0000FF);

        if (angle * conversion >= 360)
        {
            angle = 0;
        }
        else { angle+= 0.05; }
        

        window.swapBuffersToWindow();

        Sleep(16);
    }

    return 0;
}