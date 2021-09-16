#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <windows.h>
#include <locale.h>

using namespace std;

int main() {
    double N;
    cout << "enter one natural number" << endl;
    while(!(cin >> N) || N < 1 || N-(int)N != 0){
        cout << "enter one natural number" << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }
    for(int i = 0; i < 10; i++){
        cout << N << " ";
        N++;
        cout << endl;
    }
	return 0;
}