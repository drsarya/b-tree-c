#pragma once
#include <vector>  
using namespace std;
template<class T >
class Node {
 
private:
	vector<T> keys;
	vector<Node*> children;
	Node<T>* parent;
public:
	Node();
	void setParent(Node<T>* parent);
	Node<T>* getParent();
	vector<T> getKeys();
	vector<T>* getlinkKeys();
	vector<Node<T>*> getChildren();
	Node<T>* getChild(int index);
	void addChildren(vector<Node*> listNodes);
	int getIndexFromParent(Node<T>* node);

	int getIndexFromKeys(T value);
	void addChild(Node<T>* listNodes);
	void addKey(vector<T> value);
	void addKey(T value);
	void removeChild(vector<T> keys);
	void  addChildren(Node<T>* childOne, Node<T>* childTwo);
	void removeChild(int index);
	void removeKey(int index);
	int getIndexOf(vector<T >, T  value);
 int getIndexFromNode(vector<Node<T>* > v, Node<T>* value);
};