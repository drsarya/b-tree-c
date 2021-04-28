#pragma once

#include "Printer.h"
#include <iostream>
 
using namespace std;

Printer::Printer()
{
}

void Printer::printTree(Tree* tree)
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

string Printer::levelTreeToString(vector<Node*> nodes)
{
	string commonParent;
	for (Node* node : nodes) {
		for (int j = 0; j < (int)(node->getChildren().size()); j++) {
			commonParent.append(takeNodeVisual( node->getChildren().at(j)->getKeys()));
		}
		commonParent.append("  ");
	}
	return commonParent;
}
 
void Printer::walker(Node* node)
{
	if (nodes.size() == levels) {
		vector<Node*> aa = vector<Node*>();
		nodes.insert(nodes.begin()+levels, aa);
	}
	nodes.at(levels).push_back(node);
	for (int i = 0; i < (int)(node->getChildren().size()); i++) {
		levels++;
		 walker(node->getChildren().at(i));
		levels--;
	}
}
string Printer::takeNodeVisual(vector<int> keys)
{
	return "|" + getKeysAsAString(keys) + "| ";
}
string Printer::getKeysAsAString(vector<int> keys)
{
	string s;
	for (int i = 0; i < (int)(keys.size()); i++) {
		s += std::to_string(keys.at(i));
		if (i < (int)(keys.size() - 1))
			s.append(",");
	}
	return s;
}



