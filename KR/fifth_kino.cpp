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
    long long n, k;
    cin >> n >> k;
    //int floops = 0;
    long long floopsStud = 0;
    while(floopsStud * 2 + 1 < k){
        //floops++;
        floopsStud = floopsStud * 2 + 1;
    }
    long long lastLoopMin = (n - floopsStud) / (floopsStud + 1);
    long long lastLoopIncCount = (n - floopsStud) % (floopsStud + 1);
    long long studForFin = k - floopsStud;
    if(lastLoopIncCount >= studForFin){
        cout << (lastLoopMin + 1) / 2  - (lastLoopMin + 1 + 1) % 2 << endl;
        cout << (lastLoopMin + 1) / 2 << endl;
    }
    else{
        cout << (lastLoopMin) / 2  - (lastLoopMin + 1) % 2 << endl;
        cout << (lastLoopMin) / 2 << endl;
    }
    return 0;
}