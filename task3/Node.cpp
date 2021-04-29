#include "Node.h"

#include <algorithm>  // sort
#include <vector>   
using namespace std;


template<class  T>
Node<T> ::Node() {}

template<class  T>
bool comp(Node<T>* a, Node<T>* b) {
	return	 a->getKeys().at(0) < b->getKeys().at(0);
}
template<class  T>
void Node<T>  ::setParent(Node<T>* parent) { this->parent = parent; }

template<class T>
Node<T>* Node<T> ::getParent() { return parent; }

template<class  T>
vector<T> Node <T>::getKeys() { return keys; }

template<class  T>
vector<Node<T>*> Node <T>::getChildren() { return children; }

template<class  T>
Node<T>* Node<T> ::getChild(int index) { return children.at(index); }

template<class  T>
void Node<T> ::addChildren(vector<Node<T>*>  listNodes) {
	for (Node<T>* n : listNodes) {
		n->parent = this;
		children.push_back(n);
	}
	sort(children.begin(), children.end(), comp<T>);
	//Collections.sort(getChildren());
}

template<class  T>
void Node<T> ::addChildren(Node<T>* childOne, Node<T>* childTwo) {

	childOne->parent = this;
	childTwo->parent = this;
	children.push_back(childOne);
	children.push_back(childTwo);
	sort(children.begin(), children.end(), comp<T>);
	//Collections.sort(getChildren());

}
template<class  T>
int Node<T> ::getIndexFromParent(Node<T>* node) {
	return Node<T> ::getIndexFromNode(getChildren(), node);
}

template<class  T>
int Node<T> ::getIndexFromNode(vector<Node<T>* > v, Node<T>* value)
{
	for (int i = 0; i != v.size(); i++)
	{
		if (v[i] == value)
		{
			return i;
		}
	}
	return -1;
}

template<class  T>
int Node<T> ::getIndexOf(vector<T > v, T  value)
{
	for (int i = 0; i != v.size(); i++)
	{
		if (v[i] == value)
		{
			return i;
		}
	}
	return -1;
}
template<class  T>
int Node<T>::getIndexFromKeys(T value) { return  Node<T>::getIndexOf(getKeys(), value); }
template<class  T>
void Node<T> ::addChild(Node<T>* listNodes) {
	listNodes->parent = this;
	children.push_back(listNodes);
	sort(children.begin(), children.end(), comp<T>);
}

template<class  T>
void Node<T> ::addKey(vector<T> value) {

	for (T n : value) {
		keys.push_back(n);
	}
	sort(keys.begin(), keys.end());

} template<class  T>
void Node<T> ::addKey(T value) {
	keys.push_back(value);
	sort(keys.begin(), keys.end());

} template<class  T>
bool containsAll(vector<T> keysFirst, vector<T> keys) {
	if (keys.size() != keysFirst.size())
		return false;

	for (int i = 0; i != keysFirst.size(); i++)
	{
		if (keysFirst[i] != keys[i])
		{
			return false;
		}
	}
	return true;
}

template<class  T>
void Node<T> ::removeChild(vector<T> keys) {
	for (int i = 0; i < getChildren().size(); i++) {
		if (getChildren().at(i)->keys.size() == keys.size() && containsAll(children.at(i)->keys, keys)) {

			typename 	vector< Node<T>*>::iterator  pos = children.begin() + i;
			children.erase(pos);
			break;
		}
	}
}
template<class T>
vector<T>* Node<T> ::getlinkKeys() {
	return &keys;
}
template<class  T>
void Node<T> ::removeChild(int index) {
	children.erase(children.begin() + index);
}
template<class  T>
void Node<T> ::removeKey(int index) {
	(keys).erase(keys.begin() + index);
}
