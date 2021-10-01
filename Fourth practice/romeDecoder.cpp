#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <windows.h>
#include <locale.h>
#include <fstream>

using namespace std;

int findSM(string a[], int arrSize, string b){
    for(int i = 0; i < arrSize; i++){
        if(a[i] == b) return i;
    }
    return -1;
}

int main() {

    string a;
    string s = "";
    bool strGood = true;
    do{
        cout << "enter the string" << endl;
        strGood = true;
        getline(cin, a);
        for(int i = 0; i < a.size(); i++){
            if(a[i] != ' ') s += a[i];
        }
        string sC = "MDCLXVI";
        //проверка корректности строки
        //все символы хороши
        for(int i = 0; i < s.size() && strGood; i++){
            if(sC.find(s[i]) == -1) strGood = false;
        }

        //врем строка убираю вычитание
        string tmpS = "";
        for(int i = 0; i < s.size()-1 && strGood; i++){
            if(sC.find(s[i+1]) < 6 && sC.find(s[i+1]) + 2 - sC.find(s[i+1])%2 == sC.find(s[i])){
                tmpS += s[i+1];
                i++;
            }
            else if(i == s.size()-1){
                    tmpS += s[i];
                    tmpS += s[i+1];
            }
            else tmpS += s[i];
        }
        //следование символов и кол-во
        int podr = 1;
        for(int i = 1; i < tmpS.size() && strGood; i++){
            if(sC.find(s[i]) < sC.find(s[i-1])) strGood = false;
            if(s[i] == s[i-1]) podr++;
            else podr = 1;
            if(podr > 3) strGood = false;
        }


        if(!strGood) cout << "incorrect string" << endl;
    }while(!strGood);

    //строка корректна
    const int nc = 13;
    string cifr[nc] = {"I", "IV", "V", "IX", "X", "XL", "L", "XC", "C", "CD", "D", "CM", "M"};
    int cifrDec[nc] = {1, 4, 5, 9, 10, 40, 50, 90, 100, 400, 500, 900, 1000};
    int sum = 0;
    for(int i = 0; i < s.size(); i++){
        string tmpc = "";
        tmpc += s[i];
        int ind = findSM(cifr, nc, tmpc);
        if(ind == -1){
            if(i != s.size()-1){
                i++;
                tmpc += s[i];
                ind = findSM(cifr, nc, tmpc);
                if(ind == -1){
                    cout << "strange stuff happened" <<endl;
                    return 0;
                }
            }
            else{
                cout << "strange stuff happened" <<endl;
                return 0;
            }
        }
        sum += cifrDec[ind];
    }
    cout << sum << endl;
	return 0;
}
