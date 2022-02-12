#include <iostream>
#include <malloc.h>
using namespace std;


bool fiveInInt(int c){  //checking whether the number contains 5
    while(c > 0){
        int t = c % 10;
        if(t == 5) return true;
        c /= 10;
    }
    return false;
}

int main(){
    
    int n;
    cin >> n;
    int* a = (int*) malloc(n*sizeof(int));
    for(int i = 0; i < n; i++){ // array input
        cin >> a[i];
    }
    bool descending = true; //checking whether the array is descending (wow tabnine really knows what I want)
    for(int i = 1; i < n && descending; i++){
        if(a[i] >= a[i-1]) descending = false;
    }
    if(!descending){ //deleting five containing integers
        for(int i = 0; i < n; i++){
            if(fiveInInt(a[i])){
                for(int j = i+1; j < n; j++){
                    a[j-1] = a[j];
                }
                n--;
                realloc(a, n*sizeof(int));
            }
        }
    }
    else{
        cout << "array is descending insert new element" << endl;
        int t;
        cin >> t;
        bool notInserted = true;
        for(int i = 0; i < n && notInserted; i++){ //inserting new element in front of the first that is lower than the new element
            if(a[i] < t){
                n++;
                realloc(a, n*sizeof(int));
                for(int j = n-1; j > i; j--){
                    a[j] = a[j-1];
                }
                a[i] = t;
                notInserted = false;
            }
        }
        if(notInserted){
            n++;
            realloc(a, n*sizeof(int));
            a[n-1] = t;
        }
    }

    for(int i = 0; i < n; i++){
        cout << a[i] << " ";
    }

    free(a);
    return 0;
}