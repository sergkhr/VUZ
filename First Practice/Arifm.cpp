#include <iostream>
#include <limits>
#include <cmath>
#include <windows.h>
#include <locale.h>

using namespace std;

int main() {
    //окей, мне нужна помощь, как сделать вывод кириллицы, советы от гугла не помогают
    setlocale(LC_ALL, "1251");
    double a, b;
    cout << "enter two numbers" << endl;
    while(!(cin >> a >> b)){
        cout << "enter two numbers" << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }
    cout << a+b << endl;
    cout << a-b << endl;
    cout << a*b << endl;
    if(b != 0) cout << a/b << endl;
	cout << "\n";
	return 0;
}
