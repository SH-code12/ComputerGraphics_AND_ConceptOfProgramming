// Name : Shahd Elnassag
// ID : 20220533

#include <Windows.h>
#include <cmath>

int Round(double x)
{
    return (int)(x + 0.5);
}

void DrawLineBres(HDC hdc, int X1, int Y1, int X2, int Y2, COLORREF c)
{
    int dx = abs(X2 - X1);
    int dy = abs(Y2 - Y1);

    int X = X1;
    int Y = Y1;
    // increment with correct direction
    int x_inc = (X2 > X1) ? 1 : -1;
    int y_inc = (Y2 > Y1) ? 1 : -1;

    SetPixel(hdc, X, Y, c);

    if (dx > dy) {
        int d = 2 * dy - dx;
        int d1 = 2 * dy;
        int d2 = 2 * (dy - dx);

        while (X != X2) {
            if (d < 0)
                d += d1;
            else {
                d += d2;
                Y += y_inc;
            }
            X += x_inc;
            SetPixel(hdc, X, Y, c);
        }
    }
    else {
        int d = 2 * dx - dy;
        int d1 = 2 * dx;
        int d2 = 2 * (dx - dy);

        while (Y != Y2) {
            if (d < 0)
                d += d1;
            else {
                d += d2;
                X += x_inc;
            }
            Y += y_inc;
            SetPixel(hdc, X, Y, c);
        }
    }
}


int X1, Y1, X2, Y2; // Global variables to store line endpoints

LRESULT WndProc(HWND hwnd, UINT m, WPARAM wp, LPARAM lp)
{
    HDC hdc;
    switch (m)
    {
    case WM_LBUTTONDOWN:
        // Store the first click (starting point of the line)
        X1 = LOWORD(lp);
        Y1 = HIWORD(lp);
        break;

    case WM_LBUTTONUP:
    {
        // Store the second click (ending point of the line)
        X2 = LOWORD(lp);
        Y2 = HIWORD(lp);

        // Draw the line
        hdc = GetDC(hwnd);
        DrawLineBres(hdc, X1, Y1, X2, Y2, RGB(0, 0, 0));
        ReleaseDC(hwnd, hdc);
        break;
    }

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        hdc = BeginPaint(hwnd, &ps);

        // Redraw the line when window repaints
        DrawLineBres(hdc, X1, Y1, X2, Y2, RGB(0, 0, 0));

        EndPaint(hwnd, &ps);
        break;
    }

    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, m, wp, lp);
    }
    return 0;
}


int APIENTRY WinMain(HINSTANCE hi, HINSTANCE pi, LPSTR cmd, int nsh)
{
    WNDCLASS wc = {};
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
    wc.lpszClassName = L"MyClass";
    wc.lpszMenuName = NULL;
    wc.lpfnWndProc = WndProc;
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.hInstance = hi;
    RegisterClass(&wc);

    HWND hwnd = CreateWindow(L"MyClass", L"Draw My Line ^_^!", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1000, 600, NULL, NULL, hi, 0);
    ShowWindow(hwnd, nsh);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}
