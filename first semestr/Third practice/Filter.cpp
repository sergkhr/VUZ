#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <windows.h>
#include <locale.h>
#include <fstream>

using namespace std;

int main() {
    ifstream fin;
    fin.open("filterFile.txt");
    string nums = "0123456789";
    char c;
    string ans = "";
    while(!fin.eof()){
        fin.get(c);
        if(c == ' '){
            if(ans.size() > 0 && ans[ans.size()-1] != ' ') ans += c;
        }
        if(nums.find(c) != -1) ans += c;
    }
    cout << ans << endl;

    fin.close();
	return 0;
}