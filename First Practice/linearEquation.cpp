#include <iostream>
#include <cmath>

using namespace std;

int main() {
	double b, c;
    cout << "enter two number \"b\" and \"c\" - for equation bx + c = 0" << endl;
    while(!(cin >> b >> c)){
        cout << "enter two numbers" << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }
    double x; 
    if(b != 0){
        x = -1*c/b;
        cout << x << endl;
    }
    else{
        if(c == 0) cout << "infinite roots" << endl;
        else cout << "no roots" << endl;
    }
	return 0;
}