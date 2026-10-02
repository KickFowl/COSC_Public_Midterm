#include <cmath>

#include "WindowManager.h"
#include "Graphics.h"
#include "AnimationEngine.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    BITMAPINFO bitmapInfo = {};

    // Instantiate your class
    WindowManager window(&bitmapInfo, 800, 600);
    Graphics canvas(window);
    AnimationEngine animate(window);

    // Create the window
    if (!window.createWindow(hInstance, L"Software Renderer")) {
        return 0;
    }

    float angle = 1;
    float radius = 50;
    float conversion = 3.14 / 180;
    coord2D center = { 200, 200 };

    polygon2D testStartPoly = { coord2D{ 100, 200 }, coord2D{ 20, 100 }, coord2D{ 300, 150 } };
    polygon2D testEndPoly = { coord2D{ 500, 600 }, coord2D{ 300, 700 }, coord2D{ 300, 200 } };
    
    animate.setBackground(0xFF000010);


    while (window.isWindowOpen())
    {
        WindowManager::processMessages();

        animate.tweenPolygons2D(testStartPoly, testEndPoly, 0, 4000);

        //canvas.drawPolygon2D(testStartPoly);

        canvas.polygon2DRasterizer(testStartPoly, true);

        //canvas.fillRect2D(center, 100, 100);

        coord2D coord1 = { int(cos(angle) * radius) + center.x, int(sin(angle) * radius) + center.y, colors::blue };
        coord2D coord2 = { int(cos(angle) * -radius) + center.x, int(sin(angle) * -radius) + center.y };

        //canvas.drawLine2D(coord1, coord2);

        if (angle * conversion >= 360)
        {
            angle = 0;
        }
        else { angle+= 0.05; }


        canvas.draw2D();
        //animate.draw2D();

        window.swapBuffersToWindow();

        Sleep(16);
    }

    return 0;
}