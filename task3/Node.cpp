#include "Node.h"
#include <algorithm>  // sort
#include <vector>   
using namespace std;
Node::Node() {}
bool comp(Node* a, Node* b) {
	return	 a->getKeys().at(0) < b->getKeys().at(0);
}
void Node::setParent(Node* parent) { this->parent = parent; }
Node* Node::getParent() { return parent; }
vector<int> Node::getKeys() { return keys; }
vector<Node*> Node::getChildren() { return children; }
Node* Node::getChild(int index) { return children.at(index); }
void Node::addChildren(vector<Node*>  listNodes) {
	for (Node* n : listNodes) {
		n->parent = this;
		children.push_back(n);
	}
	sort(children.begin(), children.end(), comp);
	//Collections.sort(getChildren());
}

void Node::addChildren(Node* childOne, Node* childTwo) {

	childOne->parent = this;
	childTwo->parent = this;
	children.push_back(childOne);
	children.push_back(childTwo);
	sort(children.begin(), children.end(), comp);
	//Collections.sort(getChildren());
}
int Node::getIndexFromParent(Node* node) {
	return getIndexOf(getChildren(), node);
}
template<class  T>
int Node::getIndexOf(std::vector<T > v, T  num)
{
	for (int i = 0; i != v.size(); i++)
	{
		if (v[i] == num)
		{
			return i;
		}
	}
	return -1;
}

int Node::getIndexFromKeys(int value) { return  Node::getIndexOf(getKeys(), value); }
void Node::addChild(Node* listNodes) {
	listNodes->parent = this;
	children.push_back(listNodes);
	sort(children.begin(), children.end(),comp);
}
 
 
void Node::addKey(vector<int> value) {

	for (int n : value) {
		keys.push_back(n);
	}
	sort(keys.begin(), keys.end());
 
}
void Node::addKey(int value) {
	keys.push_back(value);
	sort(keys.begin(), keys.end() );
 
}
bool containsAll(vector<int> keysFirst, vector<int> keys) {
	if (keys.size() != keysFirst.size())
		return false;

	for (std::vector<int>::size_type i = 0; i != keysFirst.size(); i++)
	{
		if (keysFirst[i] != keys[i])
		{
			return false;
		}
	}
	return true;
}
void Node::removeChild(vector<int> keys) {
	for (int i = 0; i < getChildren().size(); i++) {
		if (getChildren().at(i)->keys.size() == keys.size() && containsAll(children.at(i)->keys, keys)) {
			vector<Node*>::iterator pos = children.begin() + i;
			children.erase(pos);
			break;
		}
	}
}
 
void Node::removeChild(int index) {
	children.erase(children.begin() + index);
}
void Node::removeKey(int index) {
	keys.erase(keys.begin() + index);
}
