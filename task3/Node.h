#pragma once
#include <vector>  
using namespace std;
 
class Node {
	 
private:
	vector<int> keys; 
	vector<Node*> children; 
	Node* parent;
public:
	Node();
	void setParent(Node* parent);
	Node* getParent();
	vector<int> getKeys();
 
	vector<Node*> getChildren();
	Node* getChild(int index);
	void addChildren(vector<Node*> listNodes);
	int getIndexFromParent(Node* node);
	int getIndexFromKeys(int value);
	void addChild(Node* listNodes);
	void addKey(vector<int> value);
	void addKey(int value);
	void removeChild(vector<int> keys);
	void  addChildren(Node* childOne, Node* childTwo);
	void removeChild(int index);
	void removeKey(int index);
	template<class  T>
	int getIndexOf(vector<T >, T  value);
};