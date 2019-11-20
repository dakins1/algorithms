#include <queue>
#include <vector>
#include <tuple>
#include <iostream>
#include <algorithm>
using namespace std;

void addSupersink(vector<vector<int>> &residual, const vector<int>& orders) {
    auto sz = residual.size();
    for (auto i=0; i<orders.size(); i++) {
       residual[i].push_back(orders[i]); 
    }
    //We have a new node, so it's size()1
    residual.push_back(vector<int>(residual.size()+1, 0)); //all edges (sink, v) have 0 capacity
}

//The residual represents the capacity of the graph. Therefore, each edge (u,v) with start with full capacity,
//and each edge (v,u) also starts with full capacity. 
vector<vector<int>> makeResidual(const vector<int>& orders,const vector<tuple<int,int,int>> &capacities) {
    vector<vector<int>> matrix (orders.size(), vector<int>(orders.size(), -1));
    for (auto t3 : capacities) {
        matrix[get<0>(t3)][get<1>(t3)] = get<2>(t3);
        matrix[get<1>(t3)][get<0>(t3)] = get<2>(t3);
    }
    addSupersink(matrix, orders);
	return matrix;
}


//Make a supersink. Each incoming edge to that supersink should have a capacity equal to the capacity of its
//inital edge. This is basically ensuring each city gets the flow it needs.

//Initially you thought the BFS might run forever since the counterflow edge would always cancel out the 
//actual flow edge. Well, if the counterflow edge gets you to a spot in the graph that has no available edge
//to travel, you won't have to worry about that. It will naturally box itself out. 

vector<int> bfs(const vector<vector<int>>& matrix) { //matrix is the residual graph
    vector<int> parents(matrix.size(), -1);
    vector<bool> visited (matrix.size(), false);
    vector<int> dists(matrix.size(), 1000000000);
    //Rather than parent matrix, this should return a path 
    dists[0] = 0;
    std::queue<int> myQueue;
    myQueue.push(0);
    while (!myQueue.empty()) {
        auto u = myQueue.front();
        myQueue.pop();
        if (!visited[u]) { //I really can't tell if this should be here or not
            for (auto v=0; v<matrix[u].size(); v++) { 
                //TODO Can't tell if !visited[v] should be here or not
                if (matrix[u][v]>0 && !visited[v]) { //>0 meaning there exists some flow
                    dists[v] = dists[u]+1;
                    parents[v] = u;
                    myQueue.push(v);
                }
            }
        }
        visited[u] = true;
    }
	return parents; //we return the path through the flow
}

bool isPathPresent(vector<int> parents) {
    int currNode = parents[parents.size()-1];
    while (parents[currNode] != -1) currNode = parents[currNode];
    return (currNode == 0);
}

int getMinFlow(vector<int> path, vector<vector<int>> residual) {
    if (path.size() < 2) {
        cout << "something has gone terribly wrong" << endl;
        return -100000000;
    }
    //int currNode = 2; //must start at 2, as path[0] = -1 since it is the source
    int currNode = path.size()-1; //start at sink node
    int minFlow = 1000000000;
    //TODO this could be off by one
    while (currNode > 0) { //while we haven't hit the source yet
       auto f = residual[path[currNode]][currNode];
       if (f < minFlow) minFlow = f; 
        currNode = path[currNode];
    }
    return minFlow;
}

void pushFlow(vector<vector<int>>& residual, vector<int> path, int flow) {
    int currNode = path.size()-1;
    while (currNode > 0) { //TODO same possib off by 1 as in getMinFlow
        //Here's where it breaks down. What should the residual values be?
        //I'm guessing still the capacity of each edge.
        residual[path[currNode]][currnode] += flow;
        residual[currNode][path[currNode]] -= flow;
    }
}

vector<tuple<int,int,int>> courierLoads(const vector<int> &orders, const vector<tuple<int,int,int>> &capacities) {
    auto residual = makeResidual(orders, capacities);
    vector<tuple<int,int,int>> result (capacities);
    for (auto &f : result) get<2>(f) = 0;
    auto p = bfs(residual);

    while (isPathPresent(p)) {
        auto min = getMinFlow(p, residual);    
        int currNode = path.size()-1;
        while

        p = bfs(residual);
    }

    cout << "Adj matrix" << endl;
	for (auto x : residual) { 
		for (auto y : x) {
			if (y != -1) cout << " ";
			cout << y << ", ";	
		}
		cout << endl;
	}
    for (auto x : p) cout << x << ", ";
    cout << endl;

    //change this return statement
    return capacities;
}


int main() {
	vector<int> o1 = {0,1,2,3};
	vector<tuple<int,int,int>> c1 = {
		make_tuple(0,2,3),make_tuple(0,1,3),
		make_tuple(1,2,2),make_tuple(2,3,4)
	};  
    courierLoads(o1, c1);
}
