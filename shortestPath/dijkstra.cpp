#include <unordered_set>
#include <iostream>
#include <tuple>
#include <vector>
#include <algorithm>
#include <queue>
#include <functional>

using namespace std;

int getDistance(const vector<vector<tuple<int, int>>> &adjs, int u, int v) {
   auto tups = adjs[u];
   vector<int> connections(tups.size());
   for (auto i=0; i<tups.size(); i++) {
    connections[i] = (get<0>(tups[i]));
   }
   auto iter = std::find(connections.begin(), connections.end(), v);

   //WARNING: Does not check if connection doesn't exist; shouldn't matter though since this won't
   //get called on an edge that doesn't exist
   auto d = std::distance(connections.begin(), iter);
   return get<1>(tups[d]);
}

void relax(vector<int>& dists, vector<int>& parents, int u, int v,const vector<vector<tuple<int, int>>> &adjs) {
   //watch out for overflow stuff here
    auto d = getDistance(adjs, u, v);
	cout << dists[v] << endl;
	cout << dists[u]+d << endl;
    if (dists[v] > (dists[u])+d) { //+d)) { 
		cout << "parent[v] is now " << u << endl;
        dists[v] = dists[u]+d;
        parents[v] = u;
    }


}

bool comp(tuple<int,int> u, tuple<int,int> v) { return get<1>(u) > get<1>(v); }

tuple<vector<int>, vector<int>> distanceFromHome(const vector<vector<tuple<int, int>>> &adjs) {
   //Initialize as in the book
   vector<int> dists(adjs.size(), 1000000000); 
   vector<int> parents(adjs.size(), -1);
   dists[0] = 0; //base case 

   vector<bool> visited(adjs.size(), false);

   std::priority_queue<tuple<int,int>, vector<tuple<int,int>>, 
    std::function<bool(tuple<int,int>, tuple<int,int>)> > queue(comp);
   for (auto i=0;i<dists.size(); i++) { queue.push(make_tuple(i,dists[i])); }

   while (!queue.empty()) {
    auto u = get<0>(queue.top());
    queue.pop();
	if (!visited[u]) {
    visited[u] = true;
    auto neighbors = adjs[u];
    for (auto n : neighbors) {
       	int v = get<0>(n);
		int d = get<1>(n);
		if (!visited[v]) {
		if (dists[v] > (dists[u])+d) { 
			dists[v] = dists[u]+d;
			parents[v] = u;
			queue.push(make_tuple(v, dists[v]));
		}
		}
    }
}

   }

   return make_tuple(dists, parents);
}


int main() {
   vector<vector<tuple<int,int>>> map1 = 
		{{make_tuple(1,1),make_tuple(2,3)},
		 {make_tuple(2,1),make_tuple(0,5)},
		 {make_tuple(0,3),make_tuple(1,3)}};
	auto ret1 = distanceFromHome(map1);
	vector<int> d1 = {0,1,2};
	vector<int> p1 = {-1,0,1};
	for (auto x : get<0>(ret1)) cout << x << endl;
	cout << endl;
	if(d1!=get<0>(ret1)) {
		cout << "Distance error 1" << endl;
	}
	if(p1!=get<1>(ret1)) {
		cout << "Parent error 1" << endl;
	}
	vector<vector<tuple<int,int>>> map2 = 
		{{make_tuple(1,1)},
		 {make_tuple(2,1),make_tuple(3,2)},
		 {make_tuple(4,2),make_tuple(5,3)},
		 {make_tuple(4,3)},
		 {make_tuple(2,1),make_tuple(6,2)},
		 {make_tuple(0,1),make_tuple(6,5)},
		 {}};
	auto ret2 = distanceFromHome(map2);
	for (auto x : get<0>(ret2)) cout << x << endl;
	vector<int> d2 = {0,1,2,3,4,5,6};
	vector<int> p2 = {-1,0,1,1,2,2,4};
	if(d2!=get<0>(ret2)) {
		cout << "Distance error 2" << endl;
	}
	if(p2!=get<1>(ret2)) {
		cout << "Parent error 2" << endl;
	}



	vector<vector<tuple<int,int>>> adjs = { 
        { make_tuple(1, 2), make_tuple(2, 3), make_tuple(3,1) },
        { make_tuple(0, 2), make_tuple(3, 4) },
        { make_tuple(0, 3) },
        { make_tuple(0, 1), make_tuple(1, 4) }
    };
    //distanceFromHome(adjs);


}

