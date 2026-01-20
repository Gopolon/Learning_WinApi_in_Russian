#ifndef UNICODE
#define UNICODE
#endif 

#include <iostream>
#include <windows.h>

struct pp {
    int x;
    int y;
};

void DrawCircleR(pp*& points, double R) {
    pp dot;
    const double PI = 3.1415;
    int N = 100, i;
    const double dF = 2 * PI / N;
    double angle = 0;

    for (i = 0; i < N; i++) {
        dot.x = (int)(400 + R * cos(angle));
        dot.y = (int)(400 + R * sin(angle));
        angle += dF;
        points[i] = dot;
    }
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine,
    int nCmdShow)
{
    const wchar_t CLASS_NAME[] = L"Sample Window Class";
    WNDCLASS wc = { };
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    RegisterClass(&wc);

    std::wcout << L"hello";

    // Create the window.
    HWND hwnd = CreateWindowEx(
        0,                              //                              1. Optional window styles.
        CLASS_NAME,                     //                              2. Window class
        L"Learn to Program Windows",    //                              3. Window text
        WS_OVERLAPPEDWINDOW,            //                              4. Window style
        // Size and position
        0, 0, 1920, 1080,     //5. x, y, width, height. Здесь можно было и числа указать
        NULL,       //                                                  6. Parent window    
        NULL,       //                                                  7. Menu
        hInstance,  //                                                  8. Instance handle
        NULL        //                                                  9. Additional application data
    );

    if (hwnd == NULL) { return 0; }
    ShowWindow(hwnd, nCmdShow);

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_PAINT:
    {
        pp* points = new pp[100];
        DrawCircleR(points, 250);
        int i;

        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        //Линия рисуется с помощью текущего пера и, если перо является геометрическим, текущей кистью.
        //HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 67));    X
        HPEN hPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));   //V
        SelectObject(hdc, hPen);                 //hBrush или hPen? -- Pen!

        MoveToEx(hdc, points[0].x, points[0].y, NULL);
        for (i = 1; i < 100; i++) {
            LineTo(hdc, points[i].x, points[i].y);
        }
        LineTo(hdc, points[0].x, points[0].y);

        DeleteObject(hPen);                        //hBrush или hPen? -- Pen!
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}