#include <iostream>
#include <cmath>

using namespace std;

int main() {
	double a, b, c;
    cout << "enter three numbers \"a\", \"b\" and \"c\" - for equation ax^2 + bx + c = 0" << endl;
    cin >> a >> b >> c;
    cout << "answer: "; 
    if(a != 0){
        double d = b*b - 4*a*c;
        if(d > 0){
            double x1 = (-b - sqrt(d)) / (2*a);
            double x2 = (-b + sqrt(d)) / (2*a);
            cout << x1 << "; " << x2 << endl;
        }
        else if(d == 0){
            double x = -b / (2*a);
            cout << x << endl;
        }
        else cout << "no roots" << endl;
    }
    else{
        if(b != 0){
            double x = -c/b;
            cout << x << endl;
        }
        else{
            if(c == 0) cout << "infinite roots" << endl;
            else cout << "no roots" << endl;
        }
    }
	return 0;
}