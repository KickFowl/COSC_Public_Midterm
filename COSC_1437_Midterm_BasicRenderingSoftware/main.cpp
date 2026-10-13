#include <Windows.h>

#include "WindowManager.h"
#include "Canvas.h"
#include "TwoDimensional.h"
#include "Rasterizer.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    BITMAPINFO bitmapInfo = {};

    // Instantiate your class
    WindowManager window(&bitmapInfo, 800, 600);
    Canvas canvas(window);
    TwoDimensional paint(canvas);
    Rasterizer rast(canvas);

    // Create the window
    if (!window.createWindow(hInstance, L"Software Renderer")) {
        return 0;
    }

    float angle = 1;
    float radius = 50;
    float conversion = 3.14 / 180;
    coord center = { 400, 200 };
    coord testCoord = { 200, 300 };

    polygon testStartPoly = { coord{ 100, 200 }, coord{ 150, 250 }, coord{ 200, 220 } };
    polygon testEndPoly = { coord{ 500, 600 }, coord{ 300, 700 }, coord{ 300, 200 } };
    
    canvas.setBackground(0xFF000010);


    while (window.isWindowOpen())
    {
        WindowManager::processMessages();

        coord coord1 = { int(cos(angle) * radius) + center.x, int(sin(angle) * radius) + center.y };
        coord coord2 = { int(cos(angle) * -radius) + center.x, int(sin(angle) * -radius) + center.y };

        //paint.drawLine(coord1, coord2);

        if (angle * conversion >= 360)
        {
            angle = 0;
        }
        else { angle += 0.05; }

        rast.rasterizePolygon(testStartPoly, colors::burgundy, true);

        canvas.draw();

        window.swapBuffersToWindow();

        Sleep(16);
    }

    return 0;
}