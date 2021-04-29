#pragma once

#include "Node.h"
#include "Tree.h"
#include <string>
#include <vector>   

using namespace std;

 template<class T>
 
class Printer {

private:
	int levels = 0;
	   class vector<vector<Node <T>*>> nodes = {   };
public:
	Printer();
	void printTree(Tree<T> * tree);
private:
	string levelTreeToString(vector<Node<T>*> nodes);
	void walker(Node<T>* node);
	string takeNodeVisual(vector<T> keys);
	string getKeysAsAString(vector<T> keys);

};