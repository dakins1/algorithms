

template<typename T>
class DisjointSet {
    public:
		int rank;
		DisjointSet* parent;
		const T value;
//the disjoint set itself is the node

        DisjointSet(const T &data) {
			value = data;
			rank = 0;	
			parent = this;
		}

		DisjointSet* findSet(DisjointSet* x) {
			if (x != x->parent) x->parent = findSet(x->parent);
			return x->parent;	
		}

		void Link(DisjointSet* x, DisjointSet* y) {
			if (x->rank > y->rank) y->parent = x;
			else {
				x->parent = y;
				if (x->rank == y->rank) y->rank = y->rank + 1;
			}
		}		

        void unionSets(DisjointSet &ds) {
			Link(findSet(this), findSet(ds));
		}

        const T &getMarker() {
			return value;	
		}
};

