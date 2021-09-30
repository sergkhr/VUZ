#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <windows.h>
#include <locale.h>
#include <fstream>

using namespace std;

int main() {
    ifstream fin;
    ofstream fout ("FileFile.txt");
    fout << "some random text" << endl;
    fout << "some random text again" << endl;
    fin.open("FIleFile.txt");
    char c;
    while(!fin.eof()){
        fin.get(c);
        cout << c;
    }
    fout.close();
    fin.close();
	return 0;
}