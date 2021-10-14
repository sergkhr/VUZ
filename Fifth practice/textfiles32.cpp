#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <windows.h>
#include <locale.h>
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

int main() {
    cout << -7 % 26 << endl;
    ifstream fin("file32.txt");
    string alf = "abcdefghijklmnopqrstuvwxyz";
    //шифр сдвиг в алфавите на n * номер сивола в строке + m
    int n = 2;
    int m = 10;
    if(fin.is_open()){
        while(!fin.eof()){
            string s;
            string shifr;
            getline(fin, s);
            for(int i = 0; i < s.size(); i++){
                int ind = alf.find(s[i]);
                if(ind == -1){
                    //cout << s[i];
                    shifr += s[i];
                }
                else{
                    //cout << alf[(ind + n * i + m) % alf.size()];
                    shifr += alf[(ind + n * i + m) % 26];
                }
            }
            cout << shifr << endl;
            //why is  it 9 here not -7 (alf.size() = 26)
            cout << "!" << -7 % alf.size() << endl;
            for(int i = 0; i < shifr.size(); i++){
                int ind = alf.find(shifr[i]);
                if(ind == -1) cout << shifr[i];
                else{
                    //cout << "!" << -7 % 26;
                    if((ind - n*i - m) % 26 >= 0) cout << alf[(ind - n*i - m) % 26];
                    else cout << alf[(ind - n*i - m) % 26 + 26];
                }
            }
            cout << endl;
        }
    }
    
	return 0;
}