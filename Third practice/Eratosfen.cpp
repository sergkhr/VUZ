#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <windows.h>
#include <locale.h>

using namespace std;

int main() {
    cout << "enter one integer" << endl;
    int a;
    while(!(cin >> a)){
        cout << "enter one integer" << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }
    if(a < 2) cout << "no prime numbers" << endl;
    else{
        const int n = (int)a + 1;
        int mas[n];
        mas[0] = 0; mas[1] = 0;
        for(int i = 2; i < n; i++) mas[i] = 1;
        for(int i = 2; i < n; i++){
            if(mas[i] == 1){
                cout << i << endl;
                for(int j = 2*i; j < n; j += i) mas[j] = 0;
            }
        }
    }
	return 0;
}
