
#include <iostream>
#include <vector>

using namespace std;

vector<vector<double>> buildTable(int weightLimit, const vector<int>& weights, const vector<double>& values) {

	vector<vector<double>> cache (values.size()+1, vector<double>(weightLimit+1, 0)); 

    for (int i=0; i<weightLimit; i++) { 
        cache[0][i] = 0; 
    }

	for (int i=1; i<values.size()+1; i++) {  
       //cout << "Prefix in consideration: " << i << endl;
        for (int w=0; w<weightLimit+1; w++) { //off by one errors over here?
            //cout << "i: " << i << " w: " << w << endl;
            //cout << "weightLimit: " << w << endl;
            //cout << "item's weight: " << weights[i-1] << endl;
            //cout << "item's value: " << values[i-1] << endl;
            
            if (w - weights[i-1] > -1) {
                //cout << "new value if take: " << values[i-1]+cache[i-1][w-weights[i-1]] << endl;
                //cout << "value if not take: " << cache[i-1][w] << endl;
                cache[i][w] = std::max(values[i-1] + cache[i-1][w-weights[i-1]], cache[i-1][w]);
            } else {
                //cout << "too heavy" << endl;
                //cout << "resulting value: " << cache[i-1][w] << endl;
                cache[i][w] = cache[i-1][w];
            }
        }
    }
    return cache;
}

pair<double, vector<int>> buildSolution(int weightL, vector<vector<double>> cache, const vector<int> &weights, const vector<double> &values) {

    pair<double, vector<int>> solution = std::make_pair(0.0, vector<int>());
    int weightLimit = weightL;

    for (int i=values.size(); i>0; i--) { 
            /*
            cout << "i: " << i << endl;
            cout << "curr limit: " << weightLimit << endl;
            cout << "curr weight: " << weights[i-1] << endl;
            cout << "value: " << values[i-1] << endl;
            cout << "cache[i][weightLimit]: " << cache[i][weightLimit] << endl;
            cout << "cache[i-1][weightLimit-weights[i-1]]: " << cache[i-1][weightLimit-weights[i-1]] << endl;
            */

      if (weightLimit - weights[i-1] >= 0) {
       if (cache[i][weightLimit] != cache[i-1][weightLimit]) {
            solution.first += values[i-1];
            solution.second.push_back(i-1);
            weightLimit -= weights[i-1];
            }
       }
    }
    return solution;
}

pair<double, vector<int>> buildSolution2(int weightL, vector<vector<double>> cache, vector<double>&values, int len) {
    //if (len == values.size()) re
}

pair<double,vector<int>> knapsack(int weightLimit, const vector<int> &weights, const vector<double> &values) {

    vector<vector<double>> cache = buildTable(weightLimit, weights, values);
    cout << "****Table has been built******" << endl;
    return buildSolution(weightLimit, cache, weights, values);

}


/*

int main() {
    //const vector<double> vals = { 1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0 }; 
    //const vector<int> weights = { 1,2,3,4,5,6,7,8 }; 
    //TODO The table is constructing properly, but the solution builder is not retrieving values proplery
	vector<int> weights =   {1,2,3,4,3,2};
	vector<double> values = {5,3,7,4,2,9};
    auto p = knapsack(5, weights, values);
    cout << p.first << endl;
    for (auto x : p.second) cout << x << endl;
}
*/
