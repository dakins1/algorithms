

template<class T,class F>
vector<double> fitFuncs(const vector<T> &data,const vector<F> &functions) {
	vector<vector<double>> a (data.size(), vector<double>(functions.size()));

	for (int i=0; i<functions.size(); i++) {
		for (int j=0; j<functions.size(); j++
			double sum = 0;
			for (int k=0; k<data.size(); k++) {
				sum += functions[i](data[k].x) * functions[j](data[k].x);
			}	
			a[i][j] = sum; //could be a[j][i], but also could not matter
		}
	}
	
	vector<double> b (data.size());
	for (int i=0; i<functions.size(); i++) {
		double sum = 0;
		for (int j=0; j<data.size(); j++) {
			sum += functions[j](data[i].x) * data[i].y;
		}	
		b[i] = sum;
	}

	return MyLinEqSolve(a, b);
}
