#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <windows.h>
#include <locale.h>
#include <fstream>

using namespace std;

int sign(double x){
    if(x > 0) return 1;
    else if(x == 0) return 0;
    else return -1;
}

int main() {
    cout << "enter one number" << endl;
    double a;
    while(!(cin >> a)){
        cout << "enter one number" << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }
    cout << sign(a) << endl;
	return 0;
}