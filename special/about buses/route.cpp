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
    cout << "insert point A and point B (from 1 to 10)" << endl;
    int startPoint;
    int destinationPoint;
    cin >> startPoint >> destinationPoint;
    const int n = 4;
    vector<vector<vector<int>>> routes; // route[][][]  1 - route; 2 - data for a point of a route; 3 - (0 - num of a point) (1 - time to sit) (2 - time to next point) (3 - time to previous point)
    ifstream fin("routes.txt");
    int cnt = -1;
    int input = -2;
    if(fin.is_open()) while(!fin.eof()) {
        fin >> input;
        if(input != -1){
            vector<vector<int>> oneRoute;
            cnt++;
            while(input != -1){
                vector<int> pointData;
                pointData.push_back(input);
                for(int i = 1; i < 4; i++){
                    fin >> input;
                    pointData.push_back(input); // yes it's dangerous but i'm being lazy here
                }
                oneRoute.push_back(pointData);
                fin >> input;
            }
            routes.push_back(oneRoute);
        }
        else{

        }

    }
    else{
        cout << "file is not opened" << endl;
        return 0;
    }

    //now we have our database

    // for(int i = 0; i < routes.size(); i++){
    //     for(int j = 0; j < routes[i].size(); j++){
    //         for(int k = 0; k < n; k++){
    //             cout << routes[i][j][k] << " ";
    //         }
    //         cout << endl;
    //     }
    //     cout << "================" << endl;
    // }

    return 0;
}