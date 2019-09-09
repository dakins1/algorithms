#include <iostream>
#include <vector>
using namespace std;

int main() {

    std::vector<std::vector<int>> v(10);

    std::vector<int> t;
    for (auto x : t) cout << x << endl;

    for (auto s : v) {
        for (auto x : s) {
            cout << x << endl;
        }
    }
}

