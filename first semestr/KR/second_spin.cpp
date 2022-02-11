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
    int m;
    cin >> m;
    int tr = 0;
    int ch = 0;
    if(m == 3) tr = 1;
    else if(m == 4)  ch = 1;
    else if(m >= 6){
        tr = m / 3;
        m = m % 3;
        if(m == 1){
            tr--;
            ch++;
        }
        else if(m == 2){
            tr -= 2;
            ch += 2;
        }
    }
    cout << tr << endl << ch << endl;
    return 0;
}