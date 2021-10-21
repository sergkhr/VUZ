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

using namespace std;

void test(int *a){
    a[1] = 4;
}

int main() {
    const int n = 3;
    int balls[n] = {1, 2, 3};
    test(balls);
    cout << balls[1];
    return 0;
}
