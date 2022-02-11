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

int main() {
    cout << "insert the number of countries" << endl;
    int n;
    while(!(cin >> n)){
        cout << "try again" << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }
    cout << "now insert a name of the country on one line, after that on the next line 3 positive or zero integers for golden, silver and bronze medals, next country goes after 3 integers" << endl;
    string s = "";
    int tmp;
    ofstream fout ("file22data.txt");
    for(int i = 0; i < n; i++){
        cin.ignore(INT_MAX, '\n');
        getline(cin, s);
        int och = 0;
        //cout << s << endl;
        fout << s << " ! ";
        for(int j = 0; j < 3; j++){
            while(!(cin >> tmp) || tmp < 0){
                cout << "not an integer or less than zero, try again, starting with the " << j+1 << "-d integer you tried to enter" << endl;
                cin.clear();
                cin.ignore(INT_MAX, '\n');
            }
            och += tmp * (7 - j);
            fout << tmp << " ";
        }
        fout << och << endl;
    }

    ifstream fin("file22data.txt");
    s = "";
    int gold = -1;
    string nums = "0123456789";
    vector<string> datas = {};
    vector<int> golds = {};
    while(!fin.eof()){
        getline(fin, s);
        bool flag = false;
        string goldstr = "";
        for(int i = 0; i < s.size(); i++){
            if(s[i] == '!') flag = true;
            if(flag){
                if(nums.find(s[i]) != -1){
                    goldstr += s[i];
                }
                else if(goldstr != "") break;
            }
        }
        gold = atoi(goldstr.c_str()); // convert to char* doesn't work with string
        datas.push_back(s);
        golds.push_back(gold);
    }
    for(int i = 0; i < golds.size(); i++){
        for(int j = i; j < golds.size(); j++){
            if(golds[i] < golds[j]){
                tmp = golds[i];
                golds[i] = golds[j];
                golds[j] = tmp;
                string tmpstr = datas[i];
                datas[i] = datas[j];
                datas[j] = tmpstr; 
            }
        }
    }
    fout.close();
    fout.open("file22data.txt");
    for(int i = 0; i < golds.size(); i++){
        fout << datas[i] << endl;
    }
    return 0;
}