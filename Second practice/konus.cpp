#include <iostream>
#include <cmath>
#include <windows.h>
#include <locale.h>

using namespace std;

int main() {
    double r1, r2, h;
    const double PI = acos(-1.0);
    cout << "enter three positive numbers: radius 1, radius 2, and height of the truncated cone" <<endl;
    while(!(cin >> r1 >> r2 >> h) || r1 < 0 || r2 < 0 || h < 0 || r1 == r2){
        if(r1 == r2){
            cout << "r1 = r2, this is not a cone, try again :)" << endl;
        }
        cout << "enter three positive numbers" << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }
    double V = PI * h * (r1*r1 + r1*r2 + r2 * r2) / 3;
    double l = sqrt(h*h + (r1-r2)*(r1-r2));
    double S = PI*(r1*r1 + l*(r1+r2) + r2*r2);
    cout << "V = " << V << "; " << "S = " << S << endl;
	return 0;
}
