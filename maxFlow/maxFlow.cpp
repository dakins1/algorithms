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

void addMatrixSupersink(vector<vector<int>> &residual, const vector<int>& orders) {
    auto sz = residual.size();
    for (auto i=0; i<orders.size(); i++) {
       residual[i].push_back(1); //1 since path does exist
    }
    //We have a new node, so it's size()1
    residual.push_back(vector<int>(residual.size()+1, -1)); //-1 since path doesn't exist
}


//The residual represents the capacity of the graph. Therefore, each edge (u,v) with start with full capacity,
//and each edge (v,u) also starts with full capacity. 
vector<vector<int>> makeResidual(const vector<int>& orders,const vector<tuple<int,int,int>> &capacities) {
    vector<vector<int>> matrix (orders.size(), vector<int>(orders.size(), -1));
    for (auto t3 : capacities) {
        //At the beginning, we should only traverse edges in the real graph. Therefore, counterflow edges will have
        //a flow of 0; i.e. you can only push flow through a counter edge (v, u) until flow has been pushed through
        //the edge (u, v)
        matrix[get<0>(t3)][get<1>(t3)] = get<2>(t3);
        matrix[get<1>(t3)][get<0>(t3)] = 0;
    }
    addSupersink(matrix, orders);
	return matrix;
}

vector<vector<int>> makeMatrix(const vector<int>& orders,const vector<tuple<int,int,int>> &capacities) {
    vector<vector<int>> matrix (orders.size(), vector<int>(orders.size(), -1));
    for (auto t3 : capacities) {
        matrix[get<0>(t3)][get<1>(t3)] = 1;
    }
    addMatrixSupersink(matrix, orders);
	return matrix;
}

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
                if (matrix[u][v]>0 && !visited[v]) { //>0 meaning there exists some flow and excludes the -1 edges
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
    //Order of this conditional is important. If currNode is -1, we immediately break out of the loop and don't
    //get a segFault from parents[-1]
    while (currNode != -1 && parents[currNode] != -1) { 
        currNode = parents[currNode];
    }
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
    //cout << "path :";
    //for (auto x : path) cout << x << ", ";
    //cout << endl;
    //cout << "minFlow: " << minFlow << endl;
    return minFlow;
}

void pushFlow(vector<vector<int>>& residual, vector<vector<int>> &matrix, vector<int> path, int flow) {
    int currNode = path.size()-1;
    while (currNode > 0) { //TODO same possib off by 1 as in getMinFlow
        //This deviates from the pseudocode; the addition/subtraction is flipped to match with how the residual
        //graph is represented
        if (matrix[path[currNode]][currNode] == 1) {
            residual[path[currNode]][currNode] -= flow;
            residual[currNode][path[currNode]] += flow;
        } else {
            residual[path[currNode]][currNode] -= flow;
            residual[currNode][path[currNode]] += flow;
            
        }
        currNode = path[currNode];
    }
}

bool checkOrdersMet(const vector<int> &orders, vector<vector<int>> &residual) {
    for (auto i=0; i<orders.size(); i++) {
        int sum = 0;
        for (auto j=0; j<residual[i].size(); j++) { // : residual[i]) if (f > 0) sum += f;
            //cout << "slot: " << j << ", " << i << ", " << residual[j][i] << endl;
            if (residual[j][i] > 0) sum += residual[j][i];
        }
        //cout << "needed :" << orders[i] << " ";
        //cout << "actual: " << sum << endl;
        //cout << i << " needs " << orders[i] << " got " << sum << endl;
        if (sum < orders[i]) {
            //cout << "orders not met" << endl;
            return false;
        }
    }
    //cout << "orders met " << endl;
    return true;
}

vector<tuple<int,int,int>> courierLoads(const vector<int> &orders, const vector<tuple<int,int,int>> &capacities) {
    auto residual = makeResidual(orders, capacities);
    auto matrix = makeMatrix(orders, capacities);
    /*
    *I don't think this is quite needed yet
    auto result (capacities);
    for (auto &f : result) get<2>(f) = 0;
    cout << "Res matrix, before: " << endl;
	for (auto x : residual) { 
		for (auto y : x) {
			if (y != -1) cout << " ";
			cout << y << ", ";	
		}
		cout << endl;
	}
    */
    auto p = bfs(residual);
        //for (auto x : p) cout << x << ", ";
        //cout << endl;
    while (isPathPresent(p)) {
        //for (auto x : p) cout << x << ", ";
        //cout << endl;
        auto f = getMinFlow(p, residual);    
        pushFlow(residual, matrix, p, f);
        p = bfs(residual);
    }

    /*
    cout << "Res matrix, after: " << endl;
	for (auto x : residual) { 
		for (auto y : x) {
			if (y != -1) cout << " ";
			cout << y << ", ";	
		}
		cout << endl;
	}
    */

    //change this return statement
    //TODO make this is doing what it should be
    //Have to check if the flows meet the orders
    auto b = checkOrdersMet(orders, residual);
    if (b) {
        auto result (capacities);
        for (auto& e : result) {
            get<2>(e) = residual[get<1>(e)][get<0>(e)];
            //cout << "(" << get<0>(e) << ", " << get<1>(e) << ", " << get<2>(e) << ")" << endl;
        }
        return result;
    } else return vector<tuple<int,int,int>> (0);
}


//int main() {
	//vector<int> o1 = {0,1,2,3};
	//vector<tuple<int,int,int>> c1 = {
		//make_tuple(0,2,3),make_tuple(0,1,3),
		//make_tuple(1,2,2),make_tuple(2,3,4)
	//};  
    //courierLoads(o1, c1);
//}
