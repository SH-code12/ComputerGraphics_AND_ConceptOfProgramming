// Name : Shahd Elnassag
// ID : 20220533

#include <Windows.h>
#include <cmath>

int Round(double x)
{
    return (int)(x + 0.5);
}

void Draw8Points(HDC hdc, int Xc, int Yc, int x, int y, COLORREF c) {
    SetPixel(hdc, Xc + x, Yc + y, c);
    SetPixel(hdc, Xc + x, Yc - y, c);
    SetPixel(hdc, Xc - x, Yc + y, c);
    SetPixel(hdc, Xc - x, Yc - y, c);
    SetPixel(hdc, Xc + y, Yc + x, c);
    SetPixel(hdc, Xc + y, Yc - x, c);
    SetPixel(hdc, Xc - y, Yc + x, c);
    SetPixel(hdc, Xc - y, Yc - x, c);
}

void DrawCircleBres(HDC hdc, int Xc, int Yc, int R, COLORREF c)
{
    int x = 0; int y = R; int d = 1 - R;
    int d1 = 3; int d2 = 5 - 2 * R;
    Draw8Points(hdc, Xc, Yc, x, y, c);
    while (x < y) {
        if (d < 0) {
            d += d1;
            d2 += 2;
        }
        else {
            d += d2;
            d2 += 4;
            y--;
        }
        d1 += 2;
        x++;
        Draw8Points(hdc, Xc, Yc, x, y, c);
    }
}

// New function to fill circle interior by scanline filling
void FillCircle(HDC hdc, int Xc, int Yc, int R, COLORREF fillColor)
{
    for (int y = -R; y <= R; y++) {
        // Calculate horizontal distance x_max for this y using circle equation
        int x_max = (int)sqrt(R * R - y * y);
        // Draw horizontal line from (Xc - x_max, Yc + y) to (Xc + x_max, Yc + y)
        for (int x = -x_max; x <= x_max; x++) {
            SetPixel(hdc, Xc + x, Yc + y, fillColor);
        }
    }
}

int Xc = -1, Yc = -1, R = 0;  // Initialize with invalid circle


//int Xc, Yc, R;

LRESULT WndProc(HWND hwnd, UINT m, WPARAM wp, LPARAM lp)
{
    HDC hdc;
    switch (m)
    {
    case WM_LBUTTONDOWN:
        // Set the center 
        Xc = LOWORD(lp);
        Yc = HIWORD(lp);
        break;

    case WM_LBUTTONUP:
    {
        // Calculate the radius 
        int X = LOWORD(lp);
        int Y = HIWORD(lp);
        R = Round(sqrt((X - Xc) * (X - Xc) + (Y - Yc) * (Y - Yc)));

        // Draw the circle and fill it
        hdc = GetDC(hwnd);
        DrawCircleBres(hdc, Xc, Yc, R, RGB(0, 0, 0)); // black circle outline
        FillCircle(hdc, Xc, Yc, R, RGB(0, 0, 255)); // fill with red color
        ReleaseDC(hwnd, hdc);

        break;
    }

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        hdc = BeginPaint(hwnd, &ps);

        // Redraw the circle and fill if circle is valid
        if (R > 0 && Xc >= 0 && Yc >= 0) {
            DrawCircleBres(hdc, Xc, Yc, R, RGB(0, 0, 0));
            FillCircle(hdc, Xc, Yc, R, RGB(255, 0, 0));
        }

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

    HWND hwnd = CreateWindow(L"MyClass", L"Draw My Circle Flood Fill ^_^!", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1000, 600, NULL, NULL, hi, 0);
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