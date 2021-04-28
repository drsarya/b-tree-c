#include "Tree.h"
#include <iostream>
 
Tree::Tree(int weight)
{
	this->weight = weight;
}



Node* Tree::getRoot()
{
	return root;
}

void Tree::add(int value)
{
	if (root == nullptr) {
		root = new Node();
		root->addKey(value);
	}
	else {
		walker(root, value);
	}
}

bool Tree::search(int value)
{
	findNode = nullptr;
	searchNode(value, root, true);
	return findNode != nullptr;
}

void Tree::deleteKey(int value)
{
	searchNode(value, root, false);
}

void Tree::walker(Node* node, int value)
{
	for (int i = 0; i < node->getKeys().size(); i++) {
		if (value <= node->getKeys().at(i) || value >= node->getKeys().at(i) && (node->getKeys().size() - i == 1 || value <= node->getKeys().at(i + 1))) {
			if (node->getChildren().size() == 0) {
				node->addKey(value);
				check(node->getKeys(), node);
			}
			else {
				if (value <= node->getKeys().at(i)) {
					walker(node->getChildren().at(i), value);
				}
				else {
					walker(node->getChildren().at(i + 1), value);
				}
			}
			return;
		}
	}
}
template<class  T >
vector<T*  >  Tree::subList(vector<T* > v, int  start, int end)
{
	vector<T* >  result = vector<T* >(v.begin() + start, v.begin() + end);
	return result;
}

void Tree::check(vector<int> keys, Node* currentNode)
{
	if (keys.size() > weight - 1) {
		Node* childLeft = new Node();
		Node* childRight = new Node();
		int half = keys.size() / 2;
		vector<int> vl(keys.begin(), keys.begin() + half);
		vector<int> vr(keys.begin() + half + 1, keys.end());
		childLeft->addKey(vl);
		childRight->addKey(vr);
		if (currentNode->getChildren().size() > 0) {
			childLeft->addChildren(subList(currentNode->getChildren(), 0, half + 1));
			childRight->addChildren(subList(currentNode->getChildren(), half + 1, currentNode->getChildren().size()));
		}
		if (currentNode->getParent() == nullptr) {
			Node* n = new Node();
			n->addKey(keys.at(half));
			n->addChildren(childLeft, childRight);
			root = n;
		}
		else {
			currentNode->getParent()->addKey(keys.at(half));
			currentNode->getParent()->removeChild(keys);
			currentNode->getParent()->addChildren(childLeft, childRight);
			check(currentNode->getParent()->getKeys(), currentNode->getParent());
		}
	}
}

void Tree::searchNode(int value, Node* node, bool search)
{
	for (int i = 0; i < node->getKeys().size(); i++) {
		if (value < node->getKeys().at(i)
			|| value > node->getKeys().at(i) && (node->getKeys().size() - i == 1
				|| value < node->getKeys().at(i + 1))) {
			if (value <= node->getKeys().at(i)) {
				if (node->getChildren().size() != 0) {
					searchNode(value, node->getChildren().at(i), search);
					return;
				}
			}
			else {
				if (node->getChildren().size() != 0) {
					searchNode(value, node->getChildren().at(i + 1), search);
					return;
				}
			}
		}
		else if (value == node->getKeys().at(i)) {
			if (search) {
				findNode = node;

			}
			else {
				if (node->getParent() == nullptr && node->getKeys().size() == 1 && node->getChildren().size() == 0)
					return;
				checkState(node, value);
			}
			return;

		}
	}
}

void Tree::checkState(Node* node, int value)
{
	if (node == nullptr) {
		std::cout << "Элемент не найден" << endl;
	}
	else {
		if (node->getChildren().size() == 0) {
			//лист
			int index = node->getIndexFromKeys(value);
			auto a =  node->getKeys() ;
			auto s = node->getKeys().begin();
			a.erase(node->getKeys().begin()+index)  ;
			if (node->getKeys().size() == 0) {
				checkNearNodes(node);
			}
		}
		else {
			//центральный
			merge(node, value);
		}
	}
}

void Tree::merge(Node* node, int value)
{
	int index = node->getIndexFromKeys(value);
	node->removeKey(index);
	Node* childLeft = node->getChild(index);
	Node* childRight = node->getChild(index + 1);
	childLeft->addKey(childRight->getKeys());
	//Добавление детей в левый нод
	int lastSize = -1;
	for (int i = 0; i < childRight->getChildren().size(); i++) {
		if (i == 0) {
			//пересечение детей левого и правого нодов
			childLeft->getChild(childLeft->getChildren().size() - 1)->addKey(childRight->getChild(i)->getKeys());
			lastSize = childLeft->getChildren().size();
		}
		else {
			//дети правого нода
			childLeft->addChild(childRight->getChildren().at(i));
		}
	}
	node->removeChild(index + 1);
	if (childLeft->getChildren().size() > 0 && childLeft->getChild(lastSize - 1)->getKeys().size() > weight - 1) {
		//пересечение больше M-1
		check(childLeft->getChild(lastSize - 1)->getKeys(), childLeft->getChild(lastSize - 1));
	}
	else if (childLeft->getKeys().size() > weight - 1) {
		check(childLeft->getKeys(), childLeft);
	}
	else if (childLeft->getParent()->getKeys().size() == 0) {
		checkNearNodes(childLeft->getParent());
	}
}

void Tree::checkNearNodes(Node* node)
{
	Node* parent = node->getParent();
	if (parent == nullptr) {
		node->getChild(0)->setParent(nullptr);
		root = node->getChild(0);
		return;
	}
	//index from parentNode
	int index = node->getParent()->getIndexFromParent(node);

	if (node->getKeys().size() != 0) return;
	if (index > 0 && parent->getChildren().at(index - 1)->getKeys().size() > 1) {
		//если у левого ребенка ключей больше минимального
		//set new value for current node
		node->addKey(parent->getKeys().at(index - 1));
		Node* leftChild = parent->getChild(index - 1);
		int maxValueOfLeftChild = leftChild->getKeys().at(leftChild->getKeys().size() - 1);
		//  parent->getKeys().set(index - 1, maxValueOfLeftChild);
		parent->getKeys().at(index - 1) = maxValueOfLeftChild;
		//delete key from left brother
		leftChild->removeKey(leftChild->getKeys().size() - 1);
		if (leftChild->getChildren().size() > 0) {
			//После соединения перекинуть лишнего ребенка на нод
			node->addChild(leftChild->getChildren().at(leftChild->getChildren().size() - 1));
			leftChild->removeChild(leftChild->getChildren().size() - 1);
		}
	}
	else if (index + 1 < parent->getChildren().size() && parent->getChild(index + 1)->getKeys().size() > 1) {
		//если у правого ребенка ключей больше минимального
		//set new value for current node
		node->addKey(parent->getKeys().at(index));
		Node* rightChild = parent->getChild(index + 1);

		int minValueOfRightChild = rightChild->getKeys().at(0);
		//set new value for parent
		parent->getKeys().at(index) = minValueOfRightChild;
		//parent->getKeys().set(index, minValueOfRightChild);
		//delete key from right brother
		rightChild->removeKey(0);
		if (rightChild->getChildren().size() > 0) {
			//После соединения перекинуть лишнего ребенка на нод
			node->addChild(rightChild->getChildren().at(0));
			rightChild->removeChild(0);
		}
	}
	else {
		//поделиться ключом некому
		//спускаем парент - мержим
		Node* n = new Node();
		n->addChildren(node->getChildren());
		if (index == 0) {
			n->addChildren(parent->getChild(index + 1)->getChildren());
			n->addKey(parent->getKeys().at(index));
			parent->removeKey(index);
			n->addKey(parent->getChild(index + 1)->getKeys().at(0));
			parent->removeChild(index + 1);
			parent->removeChild(index);
		}
		else {
			n->addChildren(parent->getChild(index - 1)->getChildren());
			n->addKey(parent->getKeys().at(index - 1));
			parent->removeKey(index - 1);
			n->addKey(parent->getChild(index - 1)->getKeys().at(0));
			parent->removeChild(index);
			parent->removeChild(index - 1);
		}
		parent->addChild(n);
		if (parent->getKeys().size() == 0) {
			checkNearNodes(parent);
		}
	}
}
