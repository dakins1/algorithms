#include <cmath>
#include <cstdlib>
#include <iostream>
#include <queue>
#include <functional>

using namespace std;

double newTime(double minSplit, double maxSplit) {
    return minSplit + rand()*(maxSplit-minSplit)/RAND_MAX;
}


int numCells(double endTime, double minSplit, double maxSplit) {

    int cellCount = 1;
    std::priority_queue<double, std::vector<double>, std::greater<double> > schedule;

    cellCount++;
    double n1 = newTime(minSplit, maxSplit);
    double n2 = newTime(minSplit, maxSplit);
    schedule.push(n1);
    schedule.push(n2);

    while (schedule.top() <= endTime) { 
        cellCount++;
        n1 = newTime(minSplit, maxSplit) + schedule.top();
        n2 = newTime(minSplit, maxSplit) + schedule.top();
		schedule.pop();
		if (n1 <= endTime) schedule.push(n1);
		if (n2 <= endTime) schedule.push(n2);
    }
	return cellCount;
}

/*
int main() {
    cout << numCells(3, 1, 1) << endl;
}
*/

