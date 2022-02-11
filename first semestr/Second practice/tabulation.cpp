#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <windows.h>
#include <locale.h>

using namespace std;

int main() {
    double x, y;
    for(x = -4; x <= 4; x += 0.5){
        if(x != 1){
            y = (x*x -2 * x + 2) / (x - 1);
            cout << "x:" << x << " y:" << y << endl;
        }
        else cout << "x:" << x << " y:no y" << endl;
    }
	return 0;
}