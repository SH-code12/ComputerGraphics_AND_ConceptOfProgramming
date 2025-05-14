// Name : Shahd Elnassag
// ID : 20220533

#include <Windows.h>
#include <cmath>

int Round(double x)
{
    return (int)(x + 0.5);

}

struct Point
{
    double X, Y;
    Point(double x = 0, double y = 0):X(x),Y(y){}

};
//Point operator * (double a, Point P) {
//    return Point(a * P.X, a * P.Y);
//}

//Point operator + (Point P1, Point P2) {
//    return Point( P1.X + P2.X, P1.Y + P2.Y);
//}
// Bezier Curve  i use Bezier Matrix
void BezierCurveInterpolated(HDC hdc, Point P1, COLORREF C1, Point P2, COLORREF C2, Point P3, COLORREF C3, Point P4, COLORREF C4)
{
    double alpha1 = -P1.X + 3 * P2.X - 3 * P3.X + P4.X;
    double beta1 = 3 * P1.X - 6 * P2.X + 3 * P3.X;
    double gamma1 = -3 * P1.X + 3 * P2.X;
    double sigma1 = P1.X;

    double alpha2 = -P1.Y + 3 * P2.Y - 3 * P3.Y + P4.Y;
    double beta2 = 3 * P1.Y - 6 * P2.Y + 3 * P3.Y;
    double gamma2 = -3 * P1.Y + 3 * P2.Y;
    double sigma2 = P1.Y;

    //  Red
    double R1 = GetRValue(C1), R2 = GetRValue(C2), R3 = GetRValue(C3), R4 = GetRValue(C4);
    double alphaR = -R1 + 3 * R2 - 3 * R3 + R4;
    double betaR = 3 * R1 - 6 * R2 + 3 * R3;
    double gammaR = -3 * R1 + 3 * R2;
    double sigmaR = R1;

    // Green
    double G1 = GetGValue(C1), G2 = GetGValue(C2), G3 = GetGValue(C3), G4 = GetGValue(C4);
    double alphaG = -G1 + 3 * G2 - 3 * G3 + G4;
    double betaG = 3 * G1 - 6 * G2 + 3 * G3;
    double gammaG = -3 * G1 + 3 * G2;
    double sigmaG = G1;

    // Blue
    double B1 = GetBValue(C1), B2 = GetBValue(C2), B3 = GetBValue(C3), B4 = GetBValue(C4);
    double alphaB = -B1 + 3 * B2 - 3 * B3 + B4;
    double betaB = 3 * B1 - 6 * B2 + 3 * B3;
    double gammaB = -3 * B1 + 3 * B2;
    double sigmaB = B1;

    for (double t = 0; t <= 1; t += 0.01)
    {
        int X = Round(alpha1 * (t * t * t) + beta1 * (t * t) + gamma1 * t + sigma1);
        int Y = Round(alpha2 * (t * t * t) + beta2 * (t * t) + gamma2 * t + sigma2);

        int R = Round(alphaR * t * t * t + betaR * t * t + gammaR * t + sigmaR);
        int G = Round(alphaG * t * t * t + betaG * t * t + gammaG * t + sigmaG);
        int B = Round(alphaB * t * t * t + betaB * t * t + gammaB * t + sigmaB);

        SetPixel(hdc, X, Y, RGB(R, G, B));
    }
}


// Global variables

Point Points[4];
int ClickCount = 0;
// Static
//Point P1 = Point(20, 30);
//Point P2 = Point(50, 60);
//Point P3 = Point(100, 60);
//Point P4 = Point(150, 30);

LRESULT WndProc(HWND hwnd, UINT m, WPARAM wp, LPARAM lp)
{
    HDC hdc;
    switch (m)
    {
    case WM_LBUTTONDOWN:
    {
        // Store the first click (starting point of the line)
        int x = LOWORD(lp);
        int y = HIWORD(lp);

        if (ClickCount < 4)
        {
            Points[ClickCount++] = Point(x, y);
        }

        if (ClickCount == 4)
        {
            hdc = GetDC(hwnd);
            BezierCurveInterpolated(hdc, Points[0], RGB(255, 255, 0), Points[1], RGB(255, 0, 255), Points[2], RGB(0, 0, 0), Points[3], RGB(255, 0, 0));
            ReleaseDC(hwnd, hdc);
            ClickCount = 0; // Reset for next curve
        }

        break;
    }

 

    case WM_PAINT:
    {

        PAINTSTRUCT ps;
        hdc = BeginPaint(hwnd, &ps);
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

    HWND hwnd = CreateWindow(L"MyClass", L"Draw My Bezier Curve ^_^!", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1000, 600, NULL, NULL, hi, 0);
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