#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <windows.h>
#include <locale.h>

using namespace std;

int main() {
    cout << "enter three positive numbers: S, p, n" << endl;
    double S, p, n;
    while(!(cin >> S >> p >> n) || S < 0 || p < 0 || n < 0){
        cout << "enter three positive numbers: S, p, n" << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }
    double r = p / 100;
    if(r == 0){
        cout << "ok, the formula says 0, but where did the S go? I think we'll divide S by number of full months, and all leftovers will go to the last payment" << '\n' << S / ((int)(n * 12)) << endl;
    }
    else{
        double m = S * r * pow(1+r, n)/ (12*(pow(1+r, n) - 1));
        cout << m << endl;
    }
	return 0;
}
