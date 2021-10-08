#define _USE_MATH_DEFINES
#define _WIN32_WINNT 0x0A00
#include <iostream>
#include <cmath>
#include <windows.h>
#include <locale.h>
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

int main() {

    //важно!!! нужно залинковать библиотеку gdi32 (ну если не компилится почему-то)
    HWND hwnd = GetConsoleWindow();
    HDC hdc = GetDC(hwnd);

    double sinHeight = 50; // from sin = 0 to sin = 1
    double sinWidth = 50; // from sin = 0 to sin = 1;
    for(double x = 0; x < 400; x++){
        SetPixel(hdc, x, 2*sinHeight - sinHeight * sin(x * M_PI / (sinWidth * 2)), RGB(255,255,255));
    }

    ReleaseDC(hwnd, hdc);
    cin.ignore();
	return 0;
}
