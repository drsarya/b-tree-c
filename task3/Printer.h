#pragma once

#include "Node.h"
#include "Tree.h"
#include <string>
#include <vector>   

using namespace std;
class Printer {

private:
	int levels = 0;
	vector<vector<Node*>> nodes = {   };
public:
	Printer();
	void printTree(Tree* tree);
private:
	string levelTreeToString(vector<Node*> nodes);
	void walker(Node* node);
	string takeNodeVisual(vector<int> keys);
	string getKeysAsAString(vector<int> keys);

};