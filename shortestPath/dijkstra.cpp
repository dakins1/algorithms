#include <unordered_set>
#include <iostream>
#include <tuple>
#include <vector>
#include <algorithm>
#include <queue>
#include <functional>

using namespace std;

//This isn't quadratic, but does get called for every node...., pretty disgusting
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
    if (dists[v] > (dists[u])+d) { //+d)) { 
        dists[v] = dists[u]+d;
        parents[v] = u;
    }

}

//Dr. Jiang kind of does the relaxing in line with the rest of the code
//Because he has a list of all the nearby nodes, he doesn't have to do a get distance function
//cuz he just goes through each node in nearby distances, for auto m : nearbyDistances, thus he doesn't
//have to pass anything to any function

bool comp(tuple<int,int> u, tuple<int,int> v) { return get<1>(u) < get<1>(v); }

tuple<vector<int>, vector<int>> distanceFromHome(const vector<vector<tuple<int, int>>> &adjs) {
   //Initialize as in the book
   vector<int> dists(adjs.size(), 1000000000); 
   vector<int> parents(adjs.size(), -1);

   vector<bool> visited(adjs.size(), false);

   std::priority_queue<tuple<int,int>, vector<tuple<int,int>>, 
    std::function<bool(tuple<int,int>, tuple<int,int>)> > queue(comp);
   for (auto i=0;i<dists.size(); i++) { queue.push(make_tuple(i,dists[i])); }

   while (!queue.empty()) {
    auto u = get<0>(queue.top());
    queue.pop();
    visited[u] = true;
    auto neighbors = adjs[u];
    for (auto n : neighbors) {
       int v = get<0>(n);
       relax(dists, parents, u, v, adjs);
    }
   }

    

   return make_tuple(dists, parents);
}

/*
int main() {
    vector<vector<tuple<int,int>>> adjs = { 
        { make_tuple(1, 2), make_tuple(2, 3), make_tuple(3,1) },
        { make_tuple(0, 2), make_tuple(3, 4) },
        { make_tuple(0, 3) },
        { make_tuple(0, 1), make_tuple(1, 4) }
    };
    distanceFromHome(adjs);

   vector<int> dists(adjs.size(), 1000000000); 
   dists[0] = 0;
   vector<int> parents(adjs.size(), -1);
   relax(dists, parents, 0, 1, adjs);
   cout << "Distance " << dists[1] << "parent " << parents[1] << endl;
   relax(dists, parents, 1, 3, adjs);
   cout << "Distance " << dists[3] << "parent " << parents[3] << endl;

}
*/
