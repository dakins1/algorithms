#include <vector>
#include <ctime>
#include <tuple>
#include <iostream>
#include <unordered_set>
using namespace std;


int main() {
    int size = 10000;
    vector<vector<int>> arr (size, vector<int>(size, 1));



    cout << "Starting efficient access." << endl;
    double start = clock();
    for (int i=0; i<size-1; i++) {
        for (int j=0; j<size-1; j++) {
            auto x = arr[i][j];
        }
    }
    cout << clock()-start/CLOCKS_PER_SEC << endl; 
    cout << "Starting inefficient access." << endl;
    double start1 = clock();
    for (int i=0; i<size-1; i++) {
        for (int j=0; j<size-1; j++) {
            auto x = arr[j][i];
        }
    }
    cout << clock()-start1/CLOCKS_PER_SEC << endl; 
}
