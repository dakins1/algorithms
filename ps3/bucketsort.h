#include <iostream>
#include <functional>
#include <algorithm>
#include <math.h>
#include <vector>
#include <cstdlib>

using namespace std;

template<typename T,typename K>
void bucketSort(T begin, T end, K keyFunc) {

    typename std::iterator_traits<T>::value_type D = begin;
    vector<vector<D>> buckets(10, vector<D>(end-begin));

    for(auto x = begin; x != end; x++) {
        double d = keyFunc(*x);
        cout << d << endl;
        int i = int (d*10);
        cout << "inside key-izer " << i << endl;
        buckets[i].push_back(x);
    }

    for(auto b : buckets) {
        cout << "sorting" << endl;
        std::sort(b.begin(), b.end());
    }
    vector<T> sorted;
    for(auto b : buckets) {
        cout << "inserting" << endl;
        sorted.insert(sorted.end(), b.begin(), b.end());
    }
    for (int i=0; i!=(end-begin); i++) {
        cout << "inserting again" << i << endl;
        *(begin+i) = (sorted[i]);
    }
    /*
    T blah = begin;
    for(auto x : sorted) {
       (*blah) = *x;
       blah++;
    }
    ++blah=end;
    */
}


