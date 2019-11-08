#include <vector>
#include <iostream>
using namespace std;

vector<tuple<int,int,int>> courierLoads(
	const vector<int> &orders, 
	const vector<tuple<int,int,int>> &capacities)
{
	for (auto x : orders) { cout << x << ", "; }
	cout << endl;
	for (auto x : capacities) { cout << x << ", "; }
	cout << endl;
	
}


//void main() {
    
//}
