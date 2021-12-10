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


void makeMove(vector<vector<vector<int>>> database, vector<vector<int> times, int currentPoint){

}

int main() {
    const int n = 4;
    vector<vector<vector<int>>> routes; // route[][][]  1 - route; 2 - data for a point of a route; 3 - (0 - num of a point) (1 - time to sit) (2 - time to next point) (3 - time to previous point)
    ifstream fin("routes.txt");
    int routesNum = -1;
    int input = -2;
    int dotsNum = 10;
    if(fin.is_open()) while(!fin.eof()) {
        fin >> input;
        if(input != -1){
            vector<vector<int>> oneRoute;
            routesNum++;
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

    for(int i = 0; i < routes.size(); i++){
        for(int j = 0; j < routes[i].size(); j++){
            for(int k = 0; k < n; k++){
                cout << routes[i][j][k] << " ";
            }
            cout << endl;
        }
        cout << "================" << endl;
    }

    //now we have our database

    vector<vector<vector<int>>> dotsData(dotsNum); // dotsData[][] 1 - number of a dot; 2 - one change in dots, the vector is data for it; 3 - (0 - number of a dot to where a path goes) (1 - time needed to get there) (3 - number of the route)
    for(int i = 0; i < routes.size(); i++){

        for(int j = 0; j < routes[i].size(); j++){

            vector<int> dotChangeData(3);
            if(j < routes[i].size()-1){
                dotChangeData[0] = routes[i][j+1][0];
                dotChangeData[1] = routes[i][j][1] + routes[i][j][2];
                dotChangeData[2] = i;
                dotsData[routes[i][j][0]-1].push_back(dotChangeData);
            }


            if(j >= 1){
                dotChangeData[0] = routes[i][j-1][0];
                dotChangeData[1] = routes[i][j][1] + routes[i][j][3];
                dotChangeData[2] = i;
                dotsData[routes[i][j][0]-1].push_back(dotChangeData);
            }




        }
    }

    for(int i = 0; i < dotsNum; i++){
        cout << i+1 << ") ";
        for(int j = 0; j < dotsData[i].size(); j++){
            cout << "(";
            for(int k = 0; k < 3; k++){
                cout <<dotsData[i][j][k] << " ";
            }
            cout << ") ";
        }
        cout << endl;
    }

    // now we have both databases

    cout << "insert point A and point B (from 1 to 10)" << endl;
    int startPoint;
    int destinationPoint;
    cin >> startPoint >> destinationPoint;
    if(startPoint < 1 || startPoint > 10 || destinationPoint < 1 || destinationPoint > 10){
        cout << "haha error" << endl;
        return 0;
    }

    startPoint--; //from 1 to max   became 0 to max for it to be index
    destinationPoint--;

    vector<vector<int>> getToTime(dotsNum, vector<int>(2)); //getToTime[][]    1 - point; 2 -  (0 - min time) (1 - max time)
    for(int i = 0; i < getToTime.size(); i++){
        for(int j = 0; j < getToTime[i].size(); j++){
            getToTime[i][j] = INT_MAX;
        }
    }
    getToTime[startPoint][0] = 0;
    getToTime[startPoint][1] = 0;

    makeMove(dotsData, getToTime, startPoint); //actually has to do everything

    cout << getToTime[destinationPoint][0] << " to " << getToTime[destinationPoint][1] << endl;

    return 0;
}
