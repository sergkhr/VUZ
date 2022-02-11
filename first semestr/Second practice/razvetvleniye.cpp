#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <windows.h>
#include <locale.h>

using namespace std;

int main() {
    double a, x;
    cout << "enter two numbers" << endl;
    while(!(cin >> a >> x)){
        cout << "enter two numbers" << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    } 
    double w;
    if(x == 0){
        cout << "sorry, there are no such W" << endl;
        return 0;
    }
    if(abs(x) < 1){
        w = a * (log(abs(x)) / log(M_E));
    }
    else{
        if(a < x*x){
            cout << "sorry, there are no such W" << endl;
            return 0;
        }
        else{
            w = sqrt(a - x*x);
        }
        
    }
    cout << "W = " << w << endl;
	return 0;
}