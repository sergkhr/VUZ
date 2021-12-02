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

void blocksort(vector<double>& a){
    double minz = a[0];
    double maxz = a[0];
    bool sorted = true;
    for(int i = 1; i < a.size(); i++){
        minz = min(minz, a[i]);
        maxz = max(maxz, a[i]);
        if(sorted && a[i-1] > a[i]) sorted = false;
    }
    if(sorted) return;
    double delta = maxz - minz;
    int nbl = -1;
    //if(delta < 1500-1) nbl = (int)delta+2;
    //else 
    nbl = 1500; 
    if(nbl > a.size()) nbl = a.size();
    vector <vector<double>> blocks(nbl);
    for(int i = 0; i < a.size(); i++){
        //double uppercheck = (double)a[i] - (double)minz;
        //double lowercheck = (double)maxz + 1 - (double)minz;
        //double slashcheck = ((double)a[i] - (double)minz) / ((double)maxz - (double)minz);
        blocks[(int)floor(((double)nbl-1) * ((double)a[i] - (double)minz) / ((double)maxz - (double)minz))].push_back(a[i]); // some frickin magic formula
    }

    for(int i = 0; i < nbl; i++){
        if(!blocks[i].empty()) blocksort(blocks[i]); //recursion sorting blocks
    }

    int it = 0;
    for(int i = 0; i < nbl; i++){
        for(int j = 0; j < blocks[i].size(); j++){
            a[it] = blocks[i][j];
            it++;
        }
    }
    return;
}

int main() {
    ifstream fin("9.txt");
    if(fin.is_open()){
        int n;
        fin >> n;
        vector<double> vec(n);
        vector<double> vec2(n); // it's needed
        for(int i = 0; i < n; i++){
            fin >> vec[i];
            vec2[i] = vec[i];
        }

        auto start = chrono::steady_clock::now();
        blocksort(vec);
        auto end = chrono::steady_clock::now();
        //sort(vec2.begin(), vec2.end());
        bool equal = true;
        //for(int i = 0; i < n && equal; i++){
        //    if(vec[i] != vec2[i]) equal = false;
        //}
        
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
        cout << equal << " time elapsed " << duration.count() << endl;

    }
    else{
        cout << "file's not opened" << endl;
    }
    return 0;
}