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

using namespace std;

int sdel(string del, int t, int curs, int curd){
    if(del.length() < 2) return curs + curd;
    if(del[0] == ' ') del = del.substr(1);
    int d;
    for(int i = 0; i < del.length(); i++){
        if(del[i] == ' '){
            d = stoi(del.substr(0, i));
            del = del.substr(i);
            break;
        }  
    }
    int tmp = t;
    int s = curs;
    s += sdel(del, t, curs, curd);
    while(tmp % d == 0 && tmp > 0){
        curd *= d;
        tmp /= d;
        s += sdel(del, t, curs, curd);
    }
    curs += s;
    return curs;
}

int main() {
    cout << "insert m, n"  <<endl;
    int m, n;
    while(!(cin >> m >> n)){
        cout << "try again" << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }

    auto start = chrono::high_resolution_clock::now();

    vector<int> pr(n, 0);
    for(int i = 2; i < n; i++){
        if(pr[i] == 0){
            for(int j = 2*i; j < n; j+= i){
                pr[j] = 1;
            }
        }
    }
    for(int i = m; i < n; i++){
        string str = "";
        for(int j = 2; j < i; j++){
            if(pr[j] == 0 && i % j == 0){
                str += to_string(j) + " ";
            }
        }
        //cout << str << endl;
        //cout << str << " " << sdel(str, i, 0, 1) << endl;
        if(sdel(str, i, 0, 1) == 2*i) cout << i << endl;
    }


    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << endl << "executed time: " << duration.count() << endl;

    return 0;
}