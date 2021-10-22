#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <windows.h>
#include <locale.h>

using namespace std;

int main() {
    cout << "enter two integers" << endl;
    int a, b;
    while(!(cin >> a >> b)){
        cout << "enter two integers" << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }
    if(a == 0 && b == 0){
        cout << "well, you are searching for the biggest integer there is, we can't help you";
    }
    int ta = a;
    int tb = b;
    a = max(abs(ta), abs(tb));
    b = min(abs(ta), abs(tb));
    while(b != 0){
        int t = a % b;
        a = b;
        b = t;
    }
    cout  << a << endl;
	return 0;
}
