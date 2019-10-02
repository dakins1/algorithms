

#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <queue>
#include <map>

using namespace std;

struct Node {
	Node* left;
	Node* right;
	char c;
	int frequency;	
};

const vector<int> getFrequency(const string &message) {
   vector<int> hash (255, 0);
   for (auto c : message) { hash[c]++; }
   return hash;
}

Node* createNode(char c, int freq) {
	Node* n = new Node;
	n->c = c;
	n->frequency = freq;	
	n->left = nullptr;
	n->right = nullptr;
	return n;
}

void destroy(Node* root) {
	if (root->left) destroy(root->left);
	if (root->right) destroy(root->right);
	delete root;
}	

void printTree(Node* root) {
	if (!root) return;
	cout << root->c << " " << root->frequency << endl; 
	printTree(root->left);
	printTree(root->right);
}

void addEncodings(Node* root, std::map<char, vector<bool>>& m, vector<bool> code) {
	if (root->c != '\0') m[root->c] = code;
	else {
		if (root->left) {
			vector<bool> lft = code;
			lft.push_back(false);
			addEncodings(root->left, m, lft);
		}
		if (root->right) {
			vector<bool> right = code;
			right.push_back(true);
			addEncodings(root->right, m, right);
		}
	}
}


bool comp(Node* n1, Node* n2) { return (n1->frequency > n2->frequency); }

void huffman(const string &message, vector<bool> &encoding) {

    vector<int> hash = getFrequency(message);

    std::priority_queue<Node*, vector<Node*>, std::function<bool(Node*, Node*)> > queue(comp);
		

	for (int i=0; i<hash.size(); i++) {
		if (hash[i] != 0) queue.push(createNode(i, hash[i]));
	}
	while (queue.size() >=2) {
		//cout << queue.top()->c << " " << queue.top()->frequency << endl;
		Node* n = new Node;
		n->left = queue.top();
		queue.pop();
		n->right = queue.top();
		queue.pop();
		n->frequency = n->left->frequency + n->right->frequency;
		n->c = '\0';
		queue.push(n);
	}
	Node* root = queue.top();
	queue.pop();

	std::map<char, vector<bool>> codes;
	addEncodings(root, codes, vector<bool>(0));
	for (char i : message) { 
		if (hash[i] > 0) {
			encoding.insert(encoding.end(), codes[i].begin(), codes[i].end());
		}	
	}
	for (auto i : encoding) cout << i;
	cout << endl;

	destroy(root);
}


int main() {


    const string m = "aacabqbbcdefffqqghiq";
    
    vector<bool> h (10,0);
    huffman(m, h);
    

}
