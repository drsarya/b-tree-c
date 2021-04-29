#pragma once
using namespace std;
#include <vector>   
#include "Node.h"

using namespace std;
template<class T   >
class  Tree
{
public:
	Tree(int weight);
	Node<T>* getRoot();
	void add(T value);
	bool search(T value);
	void deleteKey(T value);
private:
	Node<T>* root;
	int weight;
	Node<T>* findNode;
	void walker(Node<T>* node, T value);
	void check(vector<T> keys, Node<T>* currentNode);
	void searchNode(T value, Node<T>* node, bool search);
	void checkState(Node<T>* node, T value);
	void merge(Node<T>* node, T value);
	void checkNearNodes(Node<T>* node);
	vector<T  >  subList(vector<T > v, int  start, int end);
	vector<Node<T>* >   subList(vector<Node<T>* > v, int  start, int end);
	//vector<T* >  subList(vector<T*> v, int  start, int end);
};

