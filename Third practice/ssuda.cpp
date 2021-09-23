#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <windows.h>
#include <locale.h>

using namespace std;

int main() {
    cout << "enter three positive numbers: S, p, n" << endl;
    double S, m, n;
    while(!(cin >> S >> m >> n) || S < 0 || m < 0 || n < 0)
    {
        cout << "enter three positive numbers: S, m, n" << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }
    
    double p = 0;
    int precision = -2;
    double sdvig = 1000;
    double mcheck;
    bool movePlus = true;
    for(int i = 3; i >= precision; i--)
    {
        if(p!= 0) mcheck = S * (p/100) * pow(1+(p/100), n)/ (12*(pow(1+(p/100), n) - 1));
        while((movePlus && (p==0 || mcheck < m)) || (!movePlus && p!=0 && (mcheck > m))){
            p += sdvig;
            if(p != 0) mcheck = S * (p/100) * pow(1+(p/100), n)/ (12*(pow(1+(p/100), n) - 1));
        }
        if(mcheck == m){
            cout << p << endl;
            return 0;
        }
        else{
            movePlus = !movePlus;
            sdvig /= -10;
        }
        
    }
    cout << p << endl;
    
	return 0;
}