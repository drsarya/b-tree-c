#pragma once

#include "Printer.h"
#include <iostream>
 
using namespace std;
template<class T>
Printer<T>::Printer()
{
}
template<class T>
void Printer<T>::printTree(Tree<T> * tree)
{
	vector<string> levels = {};
	nodes = {};
	this->levels = 0;
	Printer::walker(tree->getRoot());
	levels.push_back(takeNodeVisual(tree->getRoot()->getKeys()));
	for (int i = 0; i < (int)(nodes.size() - 1); i++) {
		 string newLevelDescription = Printer::levelTreeToString(nodes.at(i));
		 levels.push_back(newLevelDescription);
	}
	for (string level : levels) {
		std::cout << level << endl;
	}
}
template<class T>
string Printer<T>::levelTreeToString(vector<Node<T>*> nodes)
{
	string commonParent;
	for (Node<T>* node : nodes) {
		for (int j = 0; j < (int)(node->getChildren().size()); j++) {
			commonParent.append(takeNodeVisual( node->getChildren().at(j)->getKeys()));
		}
		commonParent.append("  ");
	}
	return commonParent;
}
template<class T>
void Printer<T>::walker(Node<T>* node)
{
	if (nodes.size() == levels) {
		vector<Node<T>*> aa = vector<Node<T>*>();
		nodes.insert(nodes.begin()+levels, aa);
	}
	nodes.at(levels).push_back(node);
	for (int i = 0; i < (int)(node->getChildren().size()); i++) {
		levels++;
		 walker(node->getChildren().at(i));
		levels--;
	}
}
template<class T>
string Printer<T>::takeNodeVisual(vector<T> keys)
{
	return "|" + getKeysAsAString(keys) + "| ";
}
template<class T>
string Printer<T>::getKeysAsAString(vector<T> keys)
{
	string s;
	for (int i = 0; i < (int)(keys.size()); i++) {
		s += std::to_string(keys.at(i));
		if (i < (int)(keys.size() - 1))
			s.append(",");
	}
	return s;
}



