#include <iostream>
#include <cmath>

using namespace std;

int main() {
	double b, c;
    cout << "enter two number \"b\" and \"c\" - for equation bx + c = 0" << endl;
    cin >> b >> c;
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