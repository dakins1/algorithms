#include<fstream>
#include<algorithm>
#include<ctime>
#include<cstdlib>
#include<vector>
#include<iostream>
#include<utility>
#include<set>
#include<tuple>

using std::ofstream;
using std::endl;
using std::clock;
using std::vector;
using std::string;
using std::rand;
using std::cout;
using std::pair;
using std::set;
using std::tuple;
using std::make_tuple;
using std::get;
using std::sort;

vector<tuple<int,int,int>> courierLoads(const vector<int> &orders, const vector<tuple<int,int,int>> &capacities);

int system(const char *c) {
	cout << "Don't use system.\n";
	return 0;
}

bool isConsistent(const vector<int> &orders, const vector<tuple<int,int,int>> &capacities,const vector<tuple<int,int,int>> &flows) {
    vector<vector<int>> cap(orders.size(),vector<int>(orders.size(),0));
    vector<vector<int>> flow(orders.size(),vector<int>(orders.size(),0));
    for(auto t:capacities) {
        cap[get<0>(t)][get<1>(t)] = get<2>(t);
    }
    for(auto t:flows) {
        flow[get<0>(t)][get<1>(t)] = get<2>(t);
	if (get<2>(t)<0){
	  cout<<"negative flow of "<<get<2>(t)<<" from "<<get<0>(t)
		<<" to "<<get<1>(t)<<endl;
	  return false;
	}else if (get<2>(t)>cap[get<0>(t)][get<1>(t)]){
	  cout<<"over capacity on edge ("<<get<0>(t)<<","<<get<1>(t)
		<<"). "<<get<2>(t)  <<" > "
		<< cap[get<0>(t)][get<1>(t)]<<endl;
	  return false;
	}
    }
    int osum = 0;
    for(unsigned int i=0; i<orders.size(); ++i) osum += orders[i];
	int outSum = 0;
    for(unsigned int i=0; i<orders.size(); ++i) outSum += flow[0][i];
	if(osum!=outSum) {
		cout << "Outflow != orders " << osum << " " << outSum << endl;
		return false;
	}
	for(unsigned int c=1; c<orders.size(); ++c) {
		int inflow = 0;
		int outflow = 0;
		for(unsigned int c2=0; c2<orders.size(); ++c2) {
			inflow += flow[c2][c];
			outflow += flow[c][c2];
		}
		if(inflow-outflow!=orders[c]) {
			cout << "flow not conserved " << c << " " << inflow << " " << outflow << " " << orders[c] << endl;
			return false;
		}
	}

	return true;
}

int main(int argc,char** argv) {
	ofstream out("time.txt");
	std::srand(42);

	vector<int> o1 = {0,1,2,3};
	vector<tuple<int,int,int>> c1 = {
		make_tuple(0,2,3),make_tuple(0,1,3),
		make_tuple(1,2,2),make_tuple(2,3,4)
	};
	vector<tuple<int,int,int>> f1 = courierLoads(o1,c1);
	sort(f1.begin(),f1.end(),
		[] (const tuple<int,int,int> &t1,const tuple<int,int,int> &t2) 
		{ return get<0>(t1) < get<0>(t2) || (get<0>(t1)==get<0>(t2) && get<1>(t1) < get<1>(t2)); });
	vector<tuple<int,int,int>> a1 = {
		make_tuple(0,1,3),make_tuple(0,2,3),make_tuple(1,2,2),make_tuple(2,3,3)
	};
	if(f1!=a1) {
		cout << "Failed Test 1" << endl;
		return -1;
	}

	vector<int> o2 = {0,3,2,3};
	vector<tuple<int,int,int>> c2 = {
		make_tuple(0,2,5),make_tuple(0,1,2),
		make_tuple(1,2,2),make_tuple(2,3,4)
	};
	vector<tuple<int,int,int>> f2 = courierLoads(o2,c2);
	sort(f2.begin(),f2.end(),
		[] (const tuple<int,int,int> &t1,const tuple<int,int,int> &t2) 
		{ return get<0>(t1) < get<0>(t2) || (get<0>(t1)==get<0>(t2) && get<1>(t1) < get<1>(t2)); });
    cout << "actual for f2" << endl;
    for (auto e : f2) {
        cout << "(" << get<0>(e) << ", " << get<1>(e) << ", " << get<2>(e) << ")" << endl;
    }
	if(f2.size()>0) {
		cout << "Failed Test 2" << endl;
		return -1;
	}

	vector<int> o3 = {0,1,2,3};
	vector<tuple<int,int,int>> c3 = {
		make_tuple(0,2,8),make_tuple(2,1,3),make_tuple(2,3,4)
	};
	vector<tuple<int,int,int>> f3 = courierLoads(o3,c3);
	sort(f3.begin(),f3.end(),
		[] (const tuple<int,int,int> &t1,const tuple<int,int,int> &t2) 
		{ return get<0>(t1) < get<0>(t2) || (get<0>(t1)==get<0>(t2) && get<1>(t1) < get<1>(t2)); });
	vector<tuple<int,int,int>> a3 = {
		make_tuple(0,2,6),make_tuple(2,1,1),make_tuple(2,3,3)
	};
	if(f3!=a3) {
		cout << "Failed Test 3" << endl;
		return -1;
	}

	vector<int> o4(1000,0);
	vector<tuple<int,int,int>> c4;
	for(unsigned int i=0; i<o4.size(); ++i) {
		if(i>0) o4[i] = rand()%10;
		for(unsigned int j=i+1; j<o4.size(); ++j) {
			if(rand()%10<7) {
				c4.push_back(make_tuple(i,j,20));
			}
		}
	}

	vector<int> o5(500,0);
	vector<tuple<int,int,int>> c5;
	for(unsigned int i=0; i<o5.size(); ++i) {
		if(i>0) o5[i] = rand()%10;
		for(unsigned int j=i+1; j<o5.size(); ++j) {
			if(rand()%10<4) {
				c5.push_back(make_tuple(i,j,20));
			}
		}
	}

	vector<int> o6(500,0);
	vector<tuple<int,int,int>> c6;
	for(unsigned int i=0; i<o6.size(); ++i) {
		if(i>0) o6[i] = rand()%10;
		for(unsigned int j=i+1; j<o6.size(); ++j) {
			if(rand()%10<7) {
				c6.push_back(make_tuple(i,j,rand()%20+5));
			}
		}
	}

	vector<int> o7(500,0);
	vector<tuple<int,int,int>> c7;
	for(unsigned int i=0; i<o7.size(); ++i) {
		if(i>0) o7[i] = rand()%10;
		for(unsigned int j=i+1; j<o7.size(); ++j) {
			if(rand()%10<6) {
				c7.push_back(make_tuple(i,j,rand()%30+5));
			}
		}
	}


	// Do Timing
	cout << "Start timing tests." << endl;
	double start = clock();

	vector<tuple<int,int,int>> f4 = courierLoads(o4,c4);
	vector<tuple<int,int,int>> f5 = courierLoads(o5,c5);
	vector<tuple<int,int,int>> f6 = courierLoads(o6,c6);
	vector<tuple<int,int,int>> f7 = courierLoads(o7,c7);

	out << (clock()-start)/CLOCKS_PER_SEC << endl;
	out.close();
	cout << "Done timing." << endl;
	// check

	cout << f4.size() << endl;
	if(f4.size()>0 && !isConsistent(o4,c4,f4)) {
		cout << "failed test 4" << endl;
		return -1;
	}
	cout << f5.size() << endl;
	if(f5.size()>0 && !isConsistent(o5,c5,f5)) {
		cout << "failed test 5" << endl;
		return -1;
	}
	cout << f6.size() << endl;
	if(f6.size()>0 && !isConsistent(o6,c6,f6)) {
		cout << "failed test 6" << endl;
		return -1;
	}
	cout << f7.size() << endl;
	if(f7.size()>0 && !isConsistent(o7,c7,f7)) {
		cout << "failed test 7" << endl;
		return -1;
	}

	return 0;
}
