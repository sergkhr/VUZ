#include <iostream>
#include <cmath>
#include <windows.h>
#include <locale.h>

using namespace std;

int main() {
    //окей, мне нужна помощь, как сделать вывод кириллицы, советы от гугла не помогают
    setlocale(LC_ALL, "rus");
	cout << "введите два числа" << endl;
    double a, b;
    cin >> a >> b;


    cout << a+b << endl;
    cout << a-b << endl;
    cout << a*b << endl;
    if(b != 0) cout << a/b << endl;
	cout << "\n";
	return 0;
}
