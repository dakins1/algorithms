#include <vector>
#include <tuple>
#include <iostream>
using namespace std;

vector<tuple<int,int,int>> courierLoads(
	const vector<int> &orders, 
	const vector<tuple<int,int,int>> &capacities)
{
	for (auto x : orders) { cout << x << ", "; }
	cout << endl;
	for (auto x : capacities) { cout << "(" << get<0>(x)<<", "<<get<1>(x)<<", "<<get<2>(x)<<")" << endl; }
	cout << endl;
	
}


//void main() {
    
//}
