#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <windows.h>
#include <locale.h>

using namespace std;

int main() {
    double x, y, b;
    cout << "enter three numbers" << endl;
    while(!(cin >> x >> y >> b)){
        cout << "enter three numbers" << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }
    if(b < y || b < x) {
        cout << "there are no such Z" << endl;
        return 0;
    }
    double Z = (log(b-y) / log(M_E)) * sqrt(b - x);
    cout << "Z = " << Z << endl;
	return 0;
}