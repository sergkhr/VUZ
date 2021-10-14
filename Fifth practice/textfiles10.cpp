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

int lettype(char c){
    if(c == ' ') return -1;
    else{
        string gl = "euoai";
        if(gl.find(c) != -1) return 1;
        else return 0;
    }
}

int main() {
    ifstream fin("file10.txt");
    if(fin.is_open()){
        while(!fin.eof()){
            string s;
            getline(fin, s);
            string slog = "";
            bool glinsl = false;
            for(int i = 0; i < s.size(); i++){
                if(lettype(s[i]) == 1){
                    if(!glinsl){
                        slog+=s[i];
                        glinsl = true;
                    }
                    else{
                        cout << slog << " ";
                        slog = "";
                        slog += s[i];
                        glinsl = true;
                    }
                }
                else if(lettype(s[i]) == 0){
                    if(!glinsl) slog+=s[i];
                    else{
                        int nextgl = -1;
                        for(int j = i+1; j < s.size(); j++){
                            if(lettype(s[j]) == 1){
                                nextgl = j;
                                break;
                            }
                            else if(lettype(s[j]) == -1){
                                break;
                            }
                        }
                        if(nextgl == i+1){
                            cout << slog << " ";
                            slog = "";
                            slog += s[i];
                            glinsl = false;
                        }
                        else if(nextgl == -1) slog += s[i];
                        else{
                            slog += s[i];
                            cout << slog << " ";
                            slog = "";
                            glinsl = false;
                        }
                    }
                }
                else{
                    cout << slog << " ";
                    slog = "";
                    glinsl = false;
                }
            }
            cout << slog << endl;
        }
    }
    
	return 0;
}