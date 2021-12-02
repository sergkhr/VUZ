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

int find(vector<int> a, int t){
    for(int i = 0; i < a.size(); i++){
        if(a[i] == t) return i;
    }
    return -1;
}

bool check(int a){
    vector <int> n = {-1, -1, -1, -1};
    int i = 0;
    while(a > 0){
        int tmp = a % 10;
        if(find(n, tmp) == -1){
            n[i] = tmp;
            i++;
        }
        else return false;
        a/=10;
    }
    return true;
}

int main() {
    for(int i = 1000; i < 10000; i++){
        if(check(i)) cout << i << endl;
    }
    return 0;
}
