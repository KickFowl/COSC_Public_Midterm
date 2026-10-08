#include <Windows.h>

#include "WindowManager.h"
#include "Canvas.h"
#include "TwoDimensional.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    BITMAPINFO bitmapInfo = {};

    // Instantiate your class
    WindowManager window(&bitmapInfo, 800, 600);
    Canvas canvas(window);
    TwoDimensional paint(canvas);

    // Create the window
    if (!window.createWindow(hInstance, L"Software Renderer")) {
        return 0;
    }

    float angle = 1;
    float radius = 50;
    float conversion = 3.14 / 180;
    coord2D center = { 400, 200 };
    coord2D testCoord = { 200, 300 };

    polygon2D testStartPoly = { coord2D{ 100, 200 }, coord2D{ 20, 100 }, coord2D{ 300, 150 } };
    polygon2D testEndPoly = { coord2D{ 500, 600 }, coord2D{ 300, 700 }, coord2D{ 300, 200 } };
    
    canvas.setBackground(0xFF000010);


    while (window.isWindowOpen())
    {
        WindowManager::processMessages();

        coord2D coord1 = { int(cos(angle) * radius) + center.x, int(sin(angle) * radius) + center.y };
        coord2D coord2 = { int(cos(angle) * -radius) + center.x, int(sin(angle) * -radius) + center.y };

        paint.drawLine(coord1, coord2);

        if (angle * conversion >= 360)
        {
            angle = 0;
        }
        else { angle += 0.05; }

        canvas.draw2D();

        window.swapBuffersToWindow();

        Sleep(16);
    }

    return 0;
}