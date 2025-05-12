// Name : Shahd Elnassag
// ID : 20220533

#include <Windows.h>
#include <cmath>

int Round(double x)
{
    return (int)(x + 0.5);
}
// Hermit Curve 
void DrawHermitCurve(HDC hdc, int X1, int Y1, int U1, int V1, int X2, int Y2, int U2, int V2, COLORREF C1, COLORREF C2)
{
    int alpha1 = 2 * X1 + U1 - 2 * X2 + U2;
    int beta1 = -3 * X1 - 2 * U1 + 3 * X2 - U2;
    int gama1 = U1;
    int delta1 = X1;


    int alpha2 = 2 * Y1 + V1 - 2 * Y2 + V2;
    int beta2 = -3 * Y1 - 2 * V1 + 3 * Y2 - V2;
    int gama2 = V1;
    int delta2 = Y1;

    // extract colore values
    //Red Color
    int r1 = GetRValue(C1);
    int r2 = GetRValue(C2);
    // Green Color
    int g1 = GetGValue(C1);
    int g2 = GetGValue(C2);
    // Blue Color
    int b1 = GetBValue(C1);
    int b2 GetBValue(C2);

    int alphaR = r2 - r1;
    int alphaG = g2 - g1;
    int alphaB = b2 - b1;

    double numberOfPoints = 100.0;
    double step = 1.0 / numberOfPoints;

    for (double t = 0; t <= 1; t += step) {

        int X = alpha1 * (t * t * t) + beta1 * (t * t) + gama1 * t + delta1;
        int Y = alpha2 * (t * t * t) + beta2 * (t * t) + gama2 * t + delta2;

        int R = Round(alphaR * t + r1);
        int G = Round(alphaG * t + g1);
        int B = Round(alphaB * t + b1);
        //SetPixel(hdc, X, Y, RGB(R, G, B));

        SetPixel(hdc, Round(X), Round(Y), RGB(R, G, B));


    }



}


// Global variables
int X1 = 0, Y1 = 0, X2 = 0, Y2 = 0;
int U1 = 100, V1 = -200, U2 = 100, V2 = 200;

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
        DrawHermitCurve(hdc, X1, Y1, U1, V1, X2, Y2, U2, V2, RGB(255, 0, 0), RGB(255, 255, 0));
        ReleaseDC(hwnd, hdc);
        break;
    }

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        hdc = BeginPaint(hwnd, &ps);

        // Redraw the line when window repaints
        DrawHermitCurve(hdc, X1, Y1, U1, V1, X2, Y2, U2, V2, RGB(255, 0, 0), RGB(255, 255, 0));

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

    HWND hwnd = CreateWindow(L"MyClass", L"Draw My Curve ^_^!", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1000, 600, NULL, NULL, hi, 0);
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
