#include <unordered_set>
#include <iostream>
#include <tuple>
#include <vector>
#include <algorithm>

using namespace std;

//This isn't quadratic, but does get called for every node...., pretty disgusting
int getDistance(const vector<vector<tuple<int, int>>> &adjs, int u, int v) {
   auto tups = adjs[u];
   vector<int> connections(tups.size());
   for (auto i=0; i<tups.size(); i++) {
    connections.push_back(get<0>(tups[i]));
   }
   const int vc = v;
   auto iter = std::find(connections.begin(), connections.end(), vc);
   cout << *iter << endl;
   if (iter != connections.end()) return get<1>(tups[iter-connections.begin()]);
   else ;
}

void relax(vector<int>& dists, vector<int>& parents, int u, int v,const vector<vector<tuple<int, int>>> &adjs) {
   //watch out for overflow stuff here
    auto d = getDistance(adjs, u, v);
    if (dists[v] > (dists[u]+d)) { 
        dists[v] = dists[u]+d;
        parents[v] = u;
    }

}

tuple<vector<int>, vector<int>> distanceFromHome(const vector<vector<tuple<int, int>>> &adjs) {
   //Initialize as in the book
   vector<int> dists(adjs.size(), 1000000000); 
   vector<int> parents(adjs.size(), -1);

    

   return make_tuple(dists, parents);
}

int main() {
    vector<vector<tuple<int,int>>> adjs = { 
        { make_tuple(1, 2), make_tuple(2, 3), make_tuple(4,1) },
        { make_tuple(0, 2), make_tuple(4, 4) },
        { make_tuple(0, 3) },
        { make_tuple(0, 1), make_tuple(1, 4) }
    };
    distanceFromHome(adjs);

   vector<int> dists(adjs.size(), 1000000000); 
   vector<int> parents(adjs.size(), -1);
   relax(dists, parents, 0, 1, adjs);
   cout << "Distance " << dists[1] << "parent " << parents[1] << endl;
   relax(dists, parents, 1, 4, adjs);
   cout << "Distance " << dists[3] << "parent " << parents[3] << endl;

}
