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

int main() {
    int n, m;
    cout << "insert two positive integers" << endl;
    while(!(cin >> n >> m) || n <= 0 || m <= 0){
        cout << "error, insert two positive integers" << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }
    vector <vector<double> > a(n, vector<double> (m));
    bool normInput = false;
    while(!normInput){
        normInput = true;
        cout << "insert the matrix" << endl;
        for(int i = 0; i < n && normInput; i++){
            for(int j = 0; j < m && normInput; j++){
                if(!(cin >> a[i][j])){
                    normInput = false;
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                }
            }
            cin.ignore(INT_MAX, '\n');
        }
        if(!normInput){
            cout << "error, go again :)" << endl;
            cin.clear();
        }
    }

    vector<int> mins(n);
    vector<int> maxs(m);
    for(int i = 0; i < n; i++){
        double mn = a[i][0];
        int ind = 0;
        for(int j = 0; j < m; j++){
            if(a[i][j] < mn){
                mn = a[i][j];
                ind = j;
            }
        }
        mins[i] = ind;
    }
    for(int j = 0; j < m; j++){
        double mx = a[0][j];
        int ind = 0;
        for(int i = 0; i < n; i++){
            if(a[i][j] > mx){
                mx = a[i][j];
                ind = i;
            }
        }
        maxs[j] = ind;
    }
    for(int i = 0; i < n; i++){
        if(i == maxs[mins[i]]){
            cout << i+1 << " " << mins[i]+1 << endl;
        }
    }


	return 0;
}
