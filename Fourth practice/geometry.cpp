#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <windows.h>
#include <locale.h>
#include <fstream>

using namespace std;

double pryam(double a, double b){
    if(a < 0 || b < 0) return -1;
    else return a*b;
}
double treug(double a, double h){
    if(a < 0 || h < 0) return -1;
    else return a*h/2;
}
double circ(double r){
    if(r < 0) return -1;
    else return M_PI*r*r;
}

int main() {
    cout << "enter 5 positive numbers a,b - for rectangle, a1,h - for triangle, r - for circle" << endl;
    double a, b, a1, h, r;
    while(!(cin >> a >> b >> a1 >> h >> r) || a < 0 || b < 0 || a1 < 0 || h < 0 || r < 0){
        cout << "enter 5 positive numbers a,b - for rectangle, a1,h - for triangle, r - for circle" << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }
    cout << "rectangle: " << pryam(a,b) << "\ntryangle: " << treug(a1, h) << "\ncircle: " << circ(r) << endl;
	return 0;
}
