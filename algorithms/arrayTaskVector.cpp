#include <iostream>
#include <vector>
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
    vector<int> a (n);
    for(int i = 0; i < n; i++){ // array input
        cin >> a[i];
    }
    bool descending = true; //checking whether the array is descending (wow tabnine really knows what I want)
    for(int i = 1; i < n && descending; i++){
        if(a[i] >= a[i-1]) descending = false;
    }
    vector<int> deletedA(n);
    if(!descending){ //deleting five containing integers by copying needed elements into the new one
        int ind = 0;
        for(int i = 0; i < n; i++){
            if(!fiveInInt(a[i])){
                deletedA[ind] = a[i];
                ind++;
            }
        }
        deletedA.resize(ind);
        deletedA.shrink_to_fit();
        a.clear(); //in this case it's actually useless, but now you know that I can clear memory :)
        a.shrink_to_fit();

        for(int i = 0; i < deletedA.size(); i++){
            cout << deletedA[i] << " ";
        }
    }
    else{
        cout << "array is descending insert new element" << endl;
        int t;
        cin >> t;
        bool notInserted = true;
        for(int i = 0; i < n && notInserted; i++){ //inserting new element in front of the first that is lower than the new element
            if(a[i] < t){
                a.insert(a.begin() + i, t);
                notInserted = false;
            }
        }
        if(notInserted){
            a.insert(a.end(), t);
        }
        for(int i = 0; i < a.size(); i++){
            cout << a[i] << " ";
        }
    }

    return 0;
}