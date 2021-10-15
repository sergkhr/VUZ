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

bool checkstr(string a, string b){ //left string should be first in alphabetic order T/F
    string por = " abcdefghijklmnopqrstuvwxyz";
    while(a.size() < b.size()){
        a += ' ';
    }
    while(b.size() < a.size()){
        b += ' ';
    }
    for(int i = 0; i < a.size(); i++){
        if(por.find(a[i]) < por.find(b[i])) return true;
        else if(por.find(a[i]) > por.find(b[i])) return false;
    }
    return true;
}

int main() {
    ofstream fout("phone.txt");
    fout << "bra " << 8984627 << endl << "avg " << 876782641 << endl << "hran " << 87657273 << endl
    << "gran " << 677824212 << endl << "shere " << 78274991 << endl;
    vector<string> names;
    vector<string> phones;
    string s;
    ifstream fin("phone.txt");
    while(!fin.eof()){
        s = "";
        fin >> s;
        if(s != "") names.push_back(s);
        s = "";
        fin >> s;
        if(s != "") phones.push_back(s);
        fin.ignore(INT_MAX, '\n');
    }
    cout << "insert the name" << endl;
    getline(cin, s);
    while(s.size() > 0 && s[0] == ' '){
       s.erase(s.begin());
    }
    while(s.size() > 0 && s[s.size()-1] == ' '){
        s.erase(s.end());
    }
    for(int i = 0; i < names.size(); i++){
        if(s == names[i]){
            cout << phones[i] << endl;
        }
    }
    for(int i = 0; i < names.size(); i++){
        for(int j = names.size()-1; j > i; j--){
            if(!checkstr(names[j-1], names[j])){
                string tmp = names[j-1];
                names[j-1] = names[j];
                names[j] = tmp;
                tmp = phones[j-1];
                phones[j-1] = phones[j];
                phones[j] = tmp;
            }
        }
    }
    fout.close();
    fout.open("phonessorted.txt");
    for(int i = 0; i < names.size(); i++){
        fout << names[i] << " " << phones[i] << endl;
    }
	return 0;
}
