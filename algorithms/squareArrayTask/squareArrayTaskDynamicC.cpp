//doing task number 28
#include <iostream>
#include <malloc.h>

using namespace std;

int main() {
    
    int n;
    cout << "insert n" << endl;
    cin >> n;
    int** matr = (int**)malloc(n * n * sizeof(int));
    
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> matr[i][j];
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - i; j++)
        {
            int tmp = matr[i][j];
            matr[i][j] = matr[n - 1 - j][n - 1 - i];
            matr[n - 1 - j][n - 1 - i] = tmp;
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << matr[i][j] << " ";
        }
        cout << endl;
    }
    free(matr);

    return 0;
}