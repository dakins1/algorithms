#include <iostream>
#include <map>
using namespace std;

enum class Operation { plus=0, minus=1, mult=2, div=3, sqrt=4, sin=5, cos=6, tan=7 };

struct ParseTree {
    double value;
    Operation op;
    ParseTree * left;
    ParseTree * right;
};

struct Toke {
    Operation * op; 
    double value;
};


Toke parse(std::string str) {
    Toke tk;
    cout << "This is str[0]: " << str[0] << endl;
    switch(str[0]) {
        case '+':
            *(tk.op) = Operation::plus;
            tk.value = 3.4;
            cout << "Reached the case statment" << endl;
        default :
            *(tk.op) = Operation::tan; 
    }
    return tk;
}

double eval(const std::string &expr, const std::map<std::string, double> &vars) {
    

}

int main() {
    cout << "Testing 123" << endl;
    //Toke t1 = {Operation::plus, 1.2};
    Operation op = Operation::plus;
    if (op == Operation::plus) cout << "op == Operation::plus" << endl;
    //if (*(t1.op) == Operation::plus) cout << "(t1.op = Operation::plus)" << endl; 
    if (*(parse("+").op) == Operation::plus) cout << "(parse(+).op == Operation::plus" << endl;
    if (parse("+").value == 3.4) cout << "parse(+).value == 3.4" << endl;
    //else cout << "It didnt' work" << endl;
    //cout << "parse().value: " << parse("+").value << endl;
}
