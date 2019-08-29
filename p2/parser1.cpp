#include <iostream>
#include <map>
#include <set>
#include <vector>
using namespace std;

//enum class Operation { plus, minus, mult, div, sqrt, sin, cos, tan };
//set<string> nums = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"}; //should this be a char?

set<char> specialTokes = { '+', '-', '*', '/' };

double simpleEval(std::string &expr) { 
    string value1;
    while (specialTokes.find(expr[0]) == specialTokes.end() && expr.length() != 0) { 
        value1.push_back(expr[0]);
        expr.erase(0,1);
    }
    double retVal = std::stod(value1);

    char op = expr.front();
    expr.erase(0,1);
    switch(op) {
        case '+':
            retVal += simpleEval(expr);
            break;
        case '-':
            retVal -= simpleEval(expr);
            break;
        case '*':
            retVal *= simpleEval(expr);
            break;
        case '/':
            retVal /= simpleEval(expr);
            break;
    }
    return retVal;

}


int main() {
    vector<string> testKeys = { "1+1", "12-2", "3*4", "60/10" };
    map<string, int> testVals = {
        {"1+1", 2},
        {"12-2", 10},
        {"3*4", 12},
        {"60/10", 6}
    };
    for (auto i : testKeys) if (testVals[i] != simpleEval(i)) cout << "Error with " << i << endl;

    string tmp = ("123+345");
    cout << simpleEval(tmp) << endl;
    
}
