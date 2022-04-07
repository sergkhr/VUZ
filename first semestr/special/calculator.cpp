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
#include <ctime>
#include <chrono>
#include <stack>

using namespace std;

int main() {
    string s = "";
    cout << "it has begun" << endl;
    getline(cin, s);
    string acthigh = "*/";
    string actlow = "+-";
    string nums = "0123456789. ";
    string skob = "()[]";
    for(int i = 0; i < s.size(); i++){
        if(acthigh.find(s[i]) == -1 && actlow.find(s[i]) == -1 && nums.find(s[i]) == -1 && skob.find(s[i]) == -1){
            cout << "error -- wrong symbols" << endl;
            return 0;
        }
    }
    stack<char> skobprov;
    for(int i = 0; i < s.size(); i++){
        if(skob.find(s[i]) != -1 && skob.find(s[i]) % 2 == 0){
            skobprov.push(s[i]);
        }
        if(skob.find(s[i]) != -1 && skob.find(s[i]) % 2 != 0){
            if(skobprov.top() == skob[skob.find(s[i])-1]) skobprov.pop();
            else{
                cout << "error -- wrong brackets" << endl;
                return 0;
            }
        }
    }
    if(!skobprov.empty()){
        cout << "error -- wrong brackets" << endl;
        return 0;
    }

    //preparations    
    for(int i = 0; i < s.size(); i++){
        if(skob.find(s[i]) != -1 || acthigh.find(s[i]) != -1 || actlow.find(s[i]) != -1){
            if(s[i] == '-'){
                if(i < s.size() - 1 && s[i+1] != ' ' && nums.find(s[i+1]) != -1){ //it's a minus for a number (not ideal but ok)
                    if(i > 0 && s[i-1] != ' ') s = s.substr(0, i) + " " + s.substr(i);
                }
                else{
                    if(i > 0 && s[i-1] != ' ') s = s.substr(0, i) + " " + s.substr(i);
                    if(i < s.size()-1 && s[i+1] != ' ') s = s.substr(0,i+1) + " " + s.substr(i+1);
                }
            }
            else{
                if(i > 0 && s[i-1] != ' ') s = s.substr(0, i) + " " + s.substr(i);
                if(i < s.size()-1 && s[i+1] != ' ') s = s.substr(0,i+1) + " " + s.substr(i+1);
            }
            
        }
    }
    //cout << "hoba" << endl;
    for(int i = s.size()-1; i >= 0; i--){
        if(s[i] == ' ') s = s.substr(0, s.size()-1);
        else{
            s += " ";
            break;
        }
    }

    stack<char> st;
    string out = "";
    string tmp = "";
    for(int i = 0; i < s.size(); i++){
        if(skob.find(s[i]) != -1){
            // skobka
            if(skob.find(s[i]) % 2 == 0) st.push(s[i]); //opening bracket
            else{
                while(st.top() != skob[skob.find(s[i]) - 1] ){
                    out += st.top();
                    out += " ";
                    st.pop();
                }
                st.pop();
            }
        }
        else if((acthigh.find(s[i]) != -1 || actlow.find(s[i]) != -1) && (s[i] != '-' || s[i+1] == ' ') ){
            //znak
            if(actlow.find(s[i]) != -1){
                //lower priority action
                while(true){
                    if( !st.empty() && (acthigh.find(st.top()) != -1 || actlow.find(st.top()) != -1) ){
                        out += st.top();
                        out += " ";
                        //cout << "hoba" << endl;
                        st.pop();
                    }
                    else break;
                }
                
                
            }
            else{
                while(true){
                    //cout << "hoba2" << endl;
                    if( !st.empty() && (acthigh.find(st.top()) != -1) ){
                        out += st.top();
                        out += " ";
                        //cout << "hoba" << endl;
                        st.pop();
                    }
                    else break;
                }
                
            }
            st.push(s[i]);
            //cout << st.top() << endl;
        }
        else{
            //numbers
            if(s[i] != ' '){
                tmp += s[i];
            }
            else if(tmp != "") {
                out += tmp + " "; 
                tmp = "";
            }
        }
    }
    while(!st.empty()){
        //cout << "hoba3" << endl;
        out += st.top();
        out += " ";
        st.pop();
    }
    //почему при out+= st.top() + " "; ломается и выводит кривые знаки?
    //cout << out << endl;  робит

    //cout << out << endl;

    stack<double> rab;
    tmp = "";
    double first = 0;
    double second = 0;
    for(int i = 0; i < out.size(); i++){
        if(out[i] == ' '){
            if(tmp != "+" && tmp != "-" && tmp != "*" && tmp != "/"){ //we found a number -> add to stack
                //cout << tmp << endl;
                if(tmp.find('.') != -1) rab.push(stod(tmp));
                else rab.push(stoi(tmp));
                tmp = "";
            }
            else{
                //cout << "hoba" << endl;
                switch(tmp[0]){ //action met -> performing
                    case '+': 
                        second = rab.top();
                        rab.pop();
                        first = rab.top();
                        rab.pop();
                        rab.push(first + second);
                        break;
                    case '-': 
                        second = rab.top();
                        rab.pop();
                        first = rab.top();
                        rab.pop();
                        rab.push(first - second);
                        break;
                    case '*': 
                        second = rab.top();
                        rab.pop();
                        first = rab.top();
                        rab.pop();
                        rab.push(first * second);
                        break;
                    case '/': 
                        second = rab.top();
                        if(second == 0){
                            cout << "zero division error in " << out << " on pos: " << i << endl;
                            return 0; 
                        }
                        rab.pop();
                        first = rab.top();
                        rab.pop();
                        rab.push(first / second);
                        break;
                }
                tmp = "";
            }
        }
        else{
            tmp += out[i];
        }
    }
    //cout << out << endl;
    cout << rab.top() << endl;
    rab.pop();

    return 0;
}