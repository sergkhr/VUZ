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

    double sinHeight = 60; // from sin = 0 to sin = 1
    double sinWidth = 30; // from sin = 0 to sin = 1;
    double sdvigVlevo = 200;
    for(double i = 0; i < 600; i+=0.2){
        double x = i-sdvigVlevo;
        SetPixel(hdc, x+sdvigVlevo, 2*sinHeight - sinHeight * sin(x * M_PI / (sinWidth * 2)), RGB(255,255,255));

    }
    for(double i = 0; i < 600; i++){
        double x = i-sdvigVlevo;
        SetPixel(hdc, x+sdvigVlevo, 2*sinHeight, RGB(255,255,255));
    }
    for(int i = sinHeight / 2; i <= 1.5*sinHeight + 2*sinHeight; i++){
        SetPixel(hdc, sdvigVlevo, i, RGB(255,255,255));
    }

    ReleaseDC(hwnd, hdc);
    cin.ignore();
	return 0;
}
