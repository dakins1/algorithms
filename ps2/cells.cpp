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

    //NOTES: you start out with one cell and splits instantly. This automatically creates 2 more cells.
    //It's possible, though, that one of these goes beyond endTime, so you'll need to account for that
    //in the intial time creations. 
	//Another note, you might end up inserting more elements than popping, therefore unordered queue might be best :o
	//ANOTHER note, what happens if a cell creates a time that is before it's current time?
	//Also, don't confuse one cell creating two more cells, thus totalling in 3 cells.
	//	What happens is one cell becomes 2 cells

    int cellCount = 1;
    std::priority_queue<double, std::vector<double>, std::greater<double> > schedule;
    schedule.push(newTime(minSplit, maxSplit));
    schedule.push(newTime(minSplit, maxSplit));

    while (schedule.top() <= endTime) {
        cellCount++;
		minSplit = schedule.top();
		schedule.push(newTime(minSplit, maxSplit));
		schedule.push(newTime(minSplit, maxSplit));
		schedule.pop();
    }
	return cellCount;

}

int main() {
	cout << numCells(1000.0, 1, 1100) << endl;
}
