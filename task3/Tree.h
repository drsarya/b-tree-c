#pragma once
using namespace std;
#include <vector>   
#include "Node.h"

using namespace std;
class  Tree
{
public:
	Tree(int weight);
	Node* getRoot();
	void add(int value);
	bool search(int value);
	void deleteKey(int value);
private:
	Node* root;
	int weight;
	Node* findNode;
	void walker(Node* node, int value);
	void check(vector<int> keys, Node* currentNode);
	void searchNode(int value, Node* node, bool search);
	void checkState(Node* node, int value);
	void merge(Node* node, int value);
	void checkNearNodes(Node* node);
	template<class  T >
	vector<T* >  subList(vector<T* > v, int  start, int end);
};

