#include <iostream>
#include <functional>
#include <algorithm>
#include <math.h>
#include <vector>
#include <cstdlib>

using namespace std;

template<typename T,typename K>
void bucketSort(T begin, T end, K keyFunc) {

    typedef typename std::iterator_traits<T>::value_type D;
    vector<vector<D>> buckets(10, vector<D>());

    for(auto x = begin; x != end; x++) {
        double d = keyFunc(*x);
        cout << d << endl;
        int i = int (d*10);
        buckets[i].push_back(*x);
    }

    for(auto b : buckets) {
        std::sort(b.begin(), b.end(), [&keyFunc](D d1, D d2){keyFunc(d1) > keyFunc(d2));
    }

    vector<D> sorted;
    for(auto b : buckets) {
        sorted.insert(sorted.end(), b.begin(), b.end());
    }
    for (int i=0; i!=(end-begin); i++) {
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


