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

static const int n = 13;

long long perestanovka(int *a, int t, long long sum){
    bool flag = false;
    if(t == n-1){
        bool ch = true;
        for(int i = 0; i < n && ch; i++){
            //cout << a[i] << " ";
            if(a[i] == i){
                flag = true;
                ch = false;
            }
        }
        //cout << endl;
        if(flag) sum++;
        //cout << s << endl;
    }
    else{
        for(int j = t; j < n; j++){
            swap(a[t], a[j]);
            t+=1;
            sum = perestanovka(a, t, sum);
            t--;
            swap(a[t], a[j]);
        }
    }
    return sum;
}

int main() {
    int balls[n];
    for(int i =0; i < n; i++){
        balls[i] = i;
    }
    cout << perestanovka(balls, 0, 0);
    return 0;
}
