#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <windows.h>
#include <locale.h>
#include <string>

using namespace std;

int main() {
    cout << "enter a string consisting of latin letters" << endl;
    string s;
    getline(cin, s);
    string nabor = " AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz";
    string fin = "";
    for(int i = 0; i < nabor.size(); i++){
        for(int j = 0; j < s.size(); j++){
            if(s[j] == nabor[i]) fin += s[j];
        }
    }
    cout << fin << endl;
	return 0;
}
