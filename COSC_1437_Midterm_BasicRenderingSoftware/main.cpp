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
    coord2D center = { 200, 200 };

    window.setBackground(0xFF000010);

    while (window.isWindowOpen())
    {
        WindowManager::processMessages();

        window.drawLine2D(coord2D{ int(cos(angle) * radius) + center.x, int(sin(angle) * radius) + center.y }, coord2D{ int(cos(angle) * -radius) + center.x, int(sin(angle) * -radius) + center.y });

        if (angle * conversion >= 360)
        {
            angle = 0;
        }
        else { angle+= 0.05; }
        
        window.draw2D();

        window.swapBuffersToWindow();

        Sleep(16);
    }

    return 0;
}