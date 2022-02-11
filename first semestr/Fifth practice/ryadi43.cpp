#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <windows.h>
#include <locale.h>
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

int main() {

    const int n = 9;
    const int m = 6;
    int a[n] = {4, 8, 11, 15, 21, 28, 40, 87, 90};
    int b[m] = {9, 12, 14, 19, 20, 34};
    int c[n+m];
    int i = 0, j = 0;
    while(i+j < n+m){
        if(i < n && j < m){
            if(a[i] <= b[j]){
                c[i+j] = a[i];
                i++;
            }
            else{
                c[i+j] = b[j];
                j++;
            }
        }
        else if(i >= n){
            c[i+j] = b[j];
            j++;
        }
        else{
            c[i+j] = a[i];
            i++;
        }
    }
    for(i = 0; i < n+m; i++){
        cout << c[i] << " ";
    }
    cout << endl;

	return 0;
}
