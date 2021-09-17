#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <windows.h>
#include <locale.h>

using namespace std;

int main() {
    double N;
    cout << "enter one number" << endl;
    while(!(cin >> N)){
        cout << "enter one number" << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }
    if(N < 1){
        for(int i = 1; i <= 10; i++){
            cout << i << endl;
        }
        cout << endl;
    }
    else{
        if(N - (int)N > 0){
            int t = (int)N + 1;
            for(int i = 0; i < 10; i++) cout << t + i << endl;
        }
        else{
            int t = (int)N;
            for(int i = 0; i < 10; i++) cout << t + i << endl;
        }
    }
	return 0;
}
