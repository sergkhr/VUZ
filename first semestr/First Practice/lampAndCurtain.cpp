#include <iostream>
#include <cmath>

using namespace std;

int main() {
    string in;
    bool goodInput, itsDay, curtOpen, lampOn;

    do{
        goodInput = false;
        cout << "is lamp turned on? Y/N" << endl;
        cin >> in;
        if(in == "Y"){
            lampOn = true;
            goodInput = true;
        }
        else if(in == "N"){
            lampOn = false;
            goodInput = true;
        }
        else cout << "please answer \"Y\" or \"N\"" << endl;
    }
    while(!goodInput);
    if(lampOn)
    {
        cout << "the room is light" << endl;
        return 0;
    }

    do{
        goodInput = false;
        cout << "are curtains opened? Y/N" << endl;
        cin >> in;
        if(in == "Y"){
            curtOpen = true;
            goodInput = true;
        }
        else if(in == "N"){
            curtOpen = false;
            goodInput = true;
        }
        else cout << "please answer \"Y\" or \"N\"" << endl;
    }
    while(!goodInput);
    if(!curtOpen){
        cout << "the room is dark" << endl;
        return 0;
    }

    do{
        goodInput = false;
        cout << "is it day? Y/N" << endl;
        cin >> in;
        if(in == "Y"){
            itsDay = true;
            goodInput = true;
        }
        else if(in == "N"){
            itsDay = false;
            goodInput = true;
        }
        else cout << "please answer \"Y\" or \"N\"" << endl;
    }
    while(!goodInput);

    if((itsDay && curtOpen) || lampOn) cout << "the room is light" << endl;
    else cout << "the room is dark" << endl;

	return 0;
}
