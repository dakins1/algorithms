#include<tuple>
#include<vector>
#include<cmath>
#include<algorithm>
#include<iostream>
#include<deque>

using std::vector;
using std::deque;
using std::tuple;
using std::sqrt;
using std::get;
using std::make_tuple;
using std::sort;
using std::cout;
using std::endl;
using std::min;
using std::max;


vector<double> MyLUPSolve(const vector<vector<double>> &A,const vector<int> &pi,const vector<double> &b) {
	unsigned int n = A.size();
	vector<double> x(n,0.0);
	vector<double> y(n,0.0);
	for(unsigned int i=0; i<n; ++i) {
		double sum = 0.0;
		for(unsigned int j=0; j<i; ++j) sum += A[i][j]*y[j];
		y[i] = b[pi[i]]-sum;
	}
	for(unsigned int i=n-1; i<n; --i) {
		double sum = 0.0;
		for(unsigned int j=i+1; j<n; ++j) sum += A[i][j]*x[j];
		x[i] = (y[i]-sum)/A[i][i];
	}
	return x;
}

vector<int> MyLUPDecomposition(vector<vector<double>> &A) {
	unsigned int n = A.size();
	vector<int> pi(n,0);
	for(unsigned int i=0; i<n; ++i) pi[i] = i;
	for(unsigned int k=0; k<n; ++k) {
		double p = 0.0;
		unsigned int kp = -1;
		for(unsigned int i = k; i<n; ++i) {
			if(fabs(A[i][k])>p) {
				p = fabs(A[i][k]);
				kp = i;
			}
		}
		if(p==0) {
			cout << "Singular" << endl;
			return {};
		}
		std::swap(pi[k],pi[kp]);
		for(unsigned int i = 0; i<n; ++i) {
			std::swap(A[k][i],A[kp][i]);
		}
		for(unsigned int i = k+1; i<n; ++i) {
			A[i][k] /= A[k][k];
			for(unsigned int j=k+1; j<n; ++j) {
				A[i][j] -= A[i][k]*A[k][j];
			}
		}
	}
	return pi;
}

vector<double> MyLinEqSolve(vector<vector<double>> &A, const vector<double> &b){
	auto pi = MyLUPDecomposition(A);
	return MyLUPSolve(A,pi,b);
}
