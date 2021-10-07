#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <windows.h>
#include <locale.h>
#include <fstream>

using namespace std;

int main() {
    
    const int prod = 3;
    const int tov = 4;
    const int den = 2;
    int colTov[prod][tov];
    double price[tov][den];
    bool normInput = false;
    while(!normInput){
        normInput = true;
        cout << "insert matrices" << endl;
        for(int i = 0; i < prod && normInput; i++){
            for(int j = 0; j < tov && normInput; j++){
                if(!(cin >> colTov[i][j])){
                    normInput = false;
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                } 
            }
            cin.ignore(INT_MAX, '\n');
        }
        for(int i = 0; i < tov && normInput; i++){
            for(int j = 0; j < den && normInput; j++){
                if(!(cin >> price[i][j])){
                    normInput = false;
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                }
            }
            cin.ignore(INT_MAX, '\n');
        }
        if(!normInput){
            cout << "incorrect input" << endl;
            cin.clear();
            //cin.ignore(32000);
        }
    }

    double prMat[prod][den];
    for(int i = 0; i < prod; i++){
        for(int j = 0; j < den; j++){
            double sum = 0;
            for(int k = 0; k < tov; k++){
                sum += price[k][j] * colTov[i][k];
            }
            prMat[i][j] = sum;
        }
    }
    for(int i = 0; i < prod; i++){
        for(int j = 0; j < den; j++){
            cout << prMat[i][j] << " ";
        }
        cout << endl;
    }

    //1 задание
    double bigInc = -1;
    for(int i = 0; i < prod; i++){
        bigInc = max(bigInc, prMat[i][0]);
    }
    double minInc = -1;
    for(int i = 0; i < prod; i++){
        minInc = max(minInc, prMat[i][0]);
    }
    cout << "biggest income ";
    for(int i = 0; i < prod; i++){
        
        if(bigInc == prMat[i][0]){
            cout << i << " ";
        }
        
        cout << "lowest income ";
        if(minInc == prMat[i][0]){
            cout << i << " ";
        }
        cout << endl;
    }
    cout << endl;

    //2 задание
    double bigIncCom = -1;
    for(int i = 0; i < prod; i++){
        bigIncCom = max(bigInc, prMat[i][1]);
    }
    double minIncCom = -1;
    for(int i = 0; i < prod; i++){
        minIncCom = max(minInc, prMat[i][1]);
    }
    for(int i = 0; i < prod; i++){
        cout << "biggest income in commision ";
        if(bigIncCom == prMat[i][1]){
            cout << i << " ";
        }
        cout << endl;
        cout << "lowest income in commision ";
        if(minIncCom == prMat[i][1]){
            cout << i << " ";
        }
        cout << endl;
    }

    //3 задание 
    double sumDen = 0;
    for(int i = 0; i < prod; i++){
        sumDen += prMat[i][0];
    }
    cout << "all income " << sumDen << endl;

    //4 задание 
    double sumDenCom = 0;
    for(int i = 0; i < prod; i++){
        sumDenCom += prMat[i][1];
    }
    cout << "all income in commision " << sumDenCom << endl;

	return 0;
}