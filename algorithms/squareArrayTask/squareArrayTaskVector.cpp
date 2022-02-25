//doing task number 28
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {

    int n;
    cout << "insert n" << endl;
    cin >> n;
    vector <double> a(n);
    for(int i = 0; i < n; i++)
    {
        double tmp;
        cin >> tmp >> a[i]; //horizontal => we dob't need x coordinate
    }
    sort(a.begin(), a.end());
    if(n % 2 != 0)
    {
        cout << "y = " << a[n/2] << endl;
    }
    else
    {
        cout << "y = " << (a[n/2] + a[n/2 - 1]) / 2.0 << endl;
    }
    return 0;
}