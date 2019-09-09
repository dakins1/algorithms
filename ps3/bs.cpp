#include "bucketsort.h"

int main() {

    //vector<double> rands = vector<double>(1000, rand());
    vector<double> rands = { 0.5,0.2,0.8,0.25,0.08,0.4 };
    cout << rands.end()-rands.begin() << endl;
    for(auto x : rands) {
     //   std::cout << x << " ";
    }
    std::cout << std::endl;

    bucketSort(rands.begin(), rands.end(), 
        [](double d) {return d;});

    for(auto x : rands) {
       std::cout << x << " ";
    }
    std::cout << std::endl;
}
