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
    fin.open("FileFile.txt");
    if(fin.is_open()){
        char c;
        string s;
        while(!fin.eof()){
            //fin.get(c);
            //cout << c;
            getline(fin, s);
            cout << s << endl;
        }


    }
    fout.close();
    fin.close();
	return 0;
}
