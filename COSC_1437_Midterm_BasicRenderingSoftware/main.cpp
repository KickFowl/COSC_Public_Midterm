#include <Windows.h>

#include "WindowManager.h"
#include "Canvas.h"
#include "TwoDimensional.h"
#include "Rasterizer.h"
#include "Signal.h"
#include "InputHandle.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
    BITMAPINFO bitmapInfo = {};

    // Instantiate your class
    WindowManager window(&bitmapInfo, 800, 600);
    Canvas canvas(window);
    TwoDimensional paint(canvas);
    Rasterizer rast(canvas);
    InputHandle inputHandler;

    window.setInputHandler(&inputHandler);

    // Create the window
    if (!window.createWindow(hInstance, L"Software Renderer")) {
        return 0;
    }

    float angle = 1;
    float radius = 50;
    float conversion = 3.14 / 180;
    coord center = { 400, 200 };
    coord testCoord = { 200, 300 };

    polygon testPoly = { coord{ 100, 100 }, coord{ 300, 400 }, coord{ 500, 500 } };
    
    canvas.setBackground(0xFF000010);

    rastPolyDebug debugInfo;
    int selectedCoord = 5;
    coord currentCoord = {};

    while (window.isWindowOpen())
    {
        WindowManager::processMessages();

        auto events = inputHandler.passEvents();
        for (const auto& event : events) {
            std::visit([&](auto&& arg) {
                using T = std::decay_t<decltype(arg)>;

                if constexpr (std::is_same_v<T, dragStart>) {

                    if (arg.startX < debugInfo.a.x + 10 &&
                        arg.startX > debugInfo.a.x - 10 &&
                        arg.startY < debugInfo.a.y + 10 &&
                        arg.startY > debugInfo.a.y - 10)
                    {
                        currentCoord = debugInfo.a;
                    } else if 
                        (arg.startX < debugInfo.top.x + 10 &&
                        arg.startX >  debugInfo.top.x - 10 &&
                        arg.startY <  debugInfo.top.y + 10 &&
                        arg.startY >  debugInfo.top.y - 10)
                    {
                        currentCoord = debugInfo.top;
                    } else if 
                        (arg.startX < debugInfo.bottom.x + 10 &&
                        arg.startX >  debugInfo.bottom.x - 10 &&
                        arg.startY <  debugInfo.bottom.y + 10 &&
                        arg.startY >  debugInfo.bottom.y - 10)
                    {
                        currentCoord = debugInfo.bottom;
                    }

                    if (currentCoord == testPoly.pos1)
                    {
                        selectedCoord = 0;
                    }
                    if (currentCoord == testPoly.pos2)
                    {
                        selectedCoord = 1;
                    }
                    if (currentCoord == testPoly.pos3)
                    {
                        selectedCoord = 2;
                    }
                }
                else if constexpr (std::is_same_v<T, dragEvent>) {

                    if (selectedCoord == 0)
                    {
                        testPoly.pos1 = coord{float(arg.dx), float(arg.dy)};
                    }
                    if (selectedCoord == 1)
                    {
                        testPoly.pos2 = coord{ float(arg.dx), float(arg.dy) };
                    }
                    if (selectedCoord == 2)
                    {
                        testPoly.pos3 = coord{ float(arg.dx), float(arg.dy) };
                    }

                    paint.drawRect({ 0, 0 }, 20, 20, colors::red);
                }
                else if constexpr (std::is_same_v<T, dragEnd>) {

                    selectedCoord = 5;

                    paint.drawRect({ 0, 0 }, 20, 20, colors::blue);
                }
                }, event);
        }

        debugInfo = rast.rasterizeDebugPolygon(testPoly, colors::burgundy);

        paint.drawQuad(debugInfo.boundingBox, colors::green);

        paint.fillRect(coord{ 0,0 }, 20, 20, debugInfo.colorCode);

        paint.drawLine(debugInfo.a,   debugInfo.top,    colors::red);
        paint.drawLine(debugInfo.a,   debugInfo.bottom, colors::green);
        paint.drawLine(debugInfo.top, debugInfo.bottom, colors::blue);


        paint.drawRect(debugInfo.a,      10, 10, colors::red,   alignment::CENTER);
        paint.drawRect(debugInfo.top,    10, 10, colors::blue, alignment::CENTER);
        paint.drawRect(debugInfo.bottom, 10, 10, colors::green,  alignment::CENTER);

        canvas.draw();

        window.swapBuffersToWindow();

        Sleep(16);
    }

    return 0;
}