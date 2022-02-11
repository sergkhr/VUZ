#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <windows.h>
#include <locale.h>
#include <fstream>

using namespace std;

int main() {
    int n = 44;
    for(int i = 0; i < n; i++) cout << "_";
    cout << endl;
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 7; j++) cout << "* ";
        cout << "*";
        for(int j = 7*2+1; j < n; j++) cout << "_";
        cout << endl;
    }
    for(int i = 6; i < 13; i++){
        for(int j = 0; j < n; j++) cout << "_";
        cout << endl;
    }
	return 0;
}
