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


void makeMove(vector<vector<vector<int>>>& database, vector<vector<int>>& times, int currentPoint, int prevRoute){
    for(int i = 0; i < database[currentPoint].size(); i++){
        int getThereMin = database[currentPoint][i][1];
        int getThereMax = database[currentPoint][i][1];
        if(prevRoute == -1) getThereMax +=  database[currentPoint][i][2]; // adding maximum waiting time
        else if(prevRoute != database[currentPoint][i][3]) getThereMax += database[currentPoint][i][2] / 2; //change route adding waiting time (/2 is actually not logically correct)
        if(times[ database[currentPoint][i][0] ][ 1 ] > times[currentPoint][1] + getThereMax){ //new path is more efficient
            times[ database[currentPoint][i][0] ][ 0 ] = times[currentPoint][0] + getThereMin;
            times[ database[currentPoint][i][0] ][ 1 ] = times[currentPoint][1] + getThereMax;
            times[ database[currentPoint][i][0] ][ 2 ] = currentPoint;

            makeMove(database, times, database[currentPoint][i][0], database[currentPoint][i][3]); //recursion if path is more efficient (if it is not, then adding new moves is counterproductive)
        }    
    }
    return;
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

   /* for(int i = 0; i < routes.size(); i++){
        for(int j = 0; j < routes[i].size(); j++){
            for(int k = 0; k < n; k++){
                cout << routes[i][j][k] << " ";
            }
            cout << endl;
        }
        cout << "================" << endl;
    } */

    //now we have our database

    vector<vector<vector<int>>> dotsData(dotsNum); // dotsData[][] 1 - number of a dot; 2 - one change in dots, the vector is data for it; 3 - (0 - number of a dot to where a path goes) (1 - time needed to get there) (2 - time to wait) (3 - number of the route)
    for(int i = 0; i < routes.size(); i++){

        for(int j = 0; j < routes[i].size(); j++){

            vector<int> dotChangeData(4);
            if(j < routes[i].size()-1){
                dotChangeData[0] = routes[i][j+1][0] - 1; // -1 for it to be index
                dotChangeData[1] = routes[i][j][1] + routes[i][j][2];
                dotChangeData[3] = i;
                if(j >= 1) dotChangeData[2] = routes[i][j-1][2];
                else dotChangeData[2] = routes[i][j][3];
                dotsData[routes[i][j][0] - 1].push_back(dotChangeData);
            }


            if(j >= 1){
                dotChangeData[0] = routes[i][j-1][0] - 1;
                dotChangeData[1] = routes[i][j][1] + routes[i][j][3];
                dotChangeData[3] = i;
                if(j < routes[i].size()-1) dotChangeData[2] = routes[i][j+1][3];
                else dotChangeData[2] = routes[i][j][2];
                dotsData[routes[i][j][0] - 1].push_back(dotChangeData);
            }




        }
    }

  /*  for(int i = 0; i < dotsNum; i++){
        cout << i << ") ";
        for(int j = 0; j < dotsData[i].size(); j++){
            cout << "(";
            for(int k = 0; k < dotsData[i][j].size(); k++){
                cout <<dotsData[i][j][k] << " ";
            }
            cout << ") ";
        }
        cout << endl;
    } */

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

    vector<vector<int>> getToTime(dotsNum, vector<int>(3)); //getToTime[][]    1 - point; 2 -  (0 - min time) (1 - max time) (2 - previous point)
    for(int i = 0; i < getToTime.size(); i++){
        for(int j = 0; j < getToTime[i].size(); j++){
            getToTime[i][j] = INT_MAX;
        }
    }
    getToTime[startPoint][0] = 0;
    getToTime[startPoint][1] = 0;
    getToTime[startPoint][2] = -1;

    makeMove(dotsData, getToTime, startPoint, -1); //actually has to do everything

    int reversePoint = destinationPoint;
    string routeBack = "";
    while(getToTime[reversePoint][2] != -1){
        routeBack += " " + to_string(reversePoint + 1);
        if(getToTime[reversePoint][2] > dotsNum) break;
        else reversePoint = getToTime[reversePoint][2];
    }
    routeBack += " " + to_string(reversePoint + 1);
    string routeAns = "";
    string tmp = "";
    for(int i = routeBack.size()-1; i >= 0; i--){
        if(routeBack[i] != ' '){
            tmp = routeBack.substr(i, 1) + tmp;
        }
        else{
            routeAns += tmp + " ";
            tmp = "";
        }
    }
    cout << getToTime[destinationPoint][0] << " to " << getToTime[destinationPoint][1] << " (" << routeAns << ")" << endl;

    return 0;
}
