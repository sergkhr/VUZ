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
    double a, b, c;
    cin >> a >> b >> c;
    int n = floor((c - a) / b);
    cout << n << endl;
    return 0;
}