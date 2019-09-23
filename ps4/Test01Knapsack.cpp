#include<fstream>
#include<algorithm>
#include<ctime>
#include<cstdlib>
#include<vector>
#include<iostream>
#include<utility>

using std::ofstream;
using std::endl;
using std::clock;
using std::vector;
using std::string;
using std::rand;
using std::cout;
using std::pair;

double myKnapsack(int weightLimit, const vector<int> &weights, const vector<double> &values);
pair<double,vector<int> > knapsack(int weightLimit, const vector<int> &weights, const vector<double> &values);

int main(int argc,char** argv) {
	ofstream out("time.txt");
	std::srand(42);

	vector<int> weights =   {1,2,3,4,3,2};
	vector<double> values = {5,3,7,4,2,9};
	
	auto st1=knapsack(3,weights,values);
	if(st1.first!=14) {
		cout << "Failed simple test 1.\n" << endl;
		cout<< "Expected "<<14<<" got "<<st1.first <<endl;
		//return -1;
	}
	if(knapsack(5,weights,values).first!=17) {
		cout << "Failed simple test 2.\n" << endl;
		//return -1;
	}
	if(knapsack(7,weights,values).first!=21) {
		cout << "Failed simple test 3.\n" << endl;
		//return -1;
	}
	if(knapsack(9,weights,values).first!=24) {
		cout << "Failed simple test 4.\n" << endl;
		//return -1;
	}

	weights.clear();
	values.clear();
	int sum = 0;
	for(int i=0; i<80000; ++i) {
		weights.push_back(rand()%100);
		values.push_back(rand()%1000);
		sum += weights[weights.size()-1];
	}
    /*
	double myans = myKnapsack(sum/1000,weights,values);
	// Do Timing
	cout << "Start timing\n";
	double start = clock();
	pair<double,vector<int> > ans = knapsack(sum/1000,weights,values);
	cout << "Completed big 1, unchecked\n";
	knapsack(sum/2000,weights,values);
	cout << "Completed big 2, unchecked\n";
	knapsack(sum/3000,weights,values);
	cout << "Completed big 3, unchecked\n";
	knapsack(sum/4000,weights,values);
	cout << "Completed big 4, unchecked\n";
	out << (clock()-start)/CLOCKS_PER_SEC << endl;
	out.close();
	cout << "Done timing." << endl;
	// check
	if(ans.first!=myans) {
		cout << "Wrong sum: " << ans.first << " != " << myans << endl;
		return -1;
	}
	double vsum = 0.0;
	double wsum = 0.0;
	for(auto i:ans.second) {
		vsum += values[i];
		wsum += weights[i];
	}
	std::sort(ans.second.begin(),ans.second.end());
	for(unsigned int i=1; i<ans.second.size(); ++i) {
		if(ans.second[i-1]==ans.second[i]) {
			cout << "Index " << i << " was a duplicate." << endl;
			return -1;
		}
	}
	if(vsum != ans.first) {
		cout << "Inconsistent: " << vsum << " != " << ans.first << endl;
		return -1;
	}
	if(wsum > sum/1000) {
		cout << wsum << " > " << sum/1000 << endl;
		return -1;
	}
    */

	return 0;
}
