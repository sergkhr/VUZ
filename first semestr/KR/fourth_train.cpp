#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <windows.h>
#include <locale.h>
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype>
#include <vector>
#include <ctime>
#include <chrono>
#include <stack>

using namespace std;

int main() {
    const int cn = 9;
    int kupe[cn];
    for(int i = 0; i < cn; i++){
        kupe[i] = 0;
    }
    int n;
    cin >> n;
    for(int i = 0; i < n; i++){
        int mes;
        cin >> mes;
        if(mes <= 36){
            kupe[(mes-1) / 4]++;
        }
        else if(mes <= 54){
            kupe[cn - (mes - 35) / 2]++;
        }
    }
    int mx = 0;
    int s = 0;
    for(int i = 0; i < cn; i++){
        if(kupe[i] == 6){
            s++;
        }
        else{
            if(s > mx) mx = s;
            s = 0;
        }
    }
    if(s > mx) mx = s;
    cout << mx << endl;
    return 0;
}