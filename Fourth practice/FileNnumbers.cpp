#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <windows.h>
#include <locale.h>
#include <fstream>

using namespace std;

int main() {
    
    ofstream fout ("Filenums.txt");
    for(int i = 0; i < 10; i++){
        fout << 1+2*i << endl;
    }
    ifstream fin;
    fin.open("Filenums.txt");
    int s = 0;
    while(!fin.eof()){
        int t = 0;
        fin >> t;
        s += t;
    }
    cout << s << endl;
    fout.close();
    fin.close();
	return 0;
}