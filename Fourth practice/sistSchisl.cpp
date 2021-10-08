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

char tol(char c){
    return tolower(c);
}
char tou(char c){
    string check = "0123456789";
    if(check.find(c) != -1) return c;
    else return toupper(c);
}

int main() {
    cout << "enter one number (integer, but in any notation) then it's notation, then the wanted notation (maximum notation is 36)" << endl;
    string a;
    int base1, base2;
    while(!(cin >> a >> base1 >> base2) || base1 > 36 || base1 < 2 || base2 > 36 || base2 < 2){
        cout << "enter one integer then two integers: number's notation, then the wanted notation" << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }
    string sym = "0123456789abcdefghijklmnopqrstuvwxyz";
    transform(a.begin(), a.end(), a.begin(), tol);
    int sum = 0;
    for(int i = a.size()-1; i >= 0; i--){
        int ind = sym.find(a[i]);
        if(ind == -1 || ind >= base1){
            cout << "incorrect number for notation " << base1 << endl;
            return 0;
        }
        sum += ind * pow(base1, a.size()-1 - i);
    }
    string ans = "";
    while(sum > 0){
        ans = sym[sum % base2] + ans;
        sum /= base2;
    }
    //transform(ans.begin(), ans.end(), ans.begin(), tou);
    cout << ans << endl;
	return 0;
}
