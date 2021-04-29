#include "Tree.h"
#include "Node.cpp"
#include <iostream>

template<class  T >
Tree<T>::Tree(int weight)
{
	this->weight = weight;
}


template<class  T >
Node<T>* Tree<T>::getRoot()
{
	return root;
}
template<class  T >
void Tree<T>::add(T value)
{
	if (root == nullptr) {
		root = new Node<T>();
		root->addKey(value);
	}
	else {
		walker(root, value);
	}
}
template<class  T >
bool Tree<T>::search(T value)
{
	findNode = nullptr;
	searchNode(value, root, true);
	return findNode != nullptr;
}
template<class  T >
void Tree<T>::deleteKey(T value)
{
	findNode = nullptr;
	searchNode(value, root, false);
	if (findNode == nullptr) {
		std::cout << "Элемент " << value << " не найден " << endl;
	}

}
template<class  T >
void Tree<T>::walker(Node<T>* node, T value)
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
vector<Node<T>*  >  Tree<T >::subList(vector<Node<T>* > v, int  start, int end)
{
	vector<Node<T>* >  result = vector<Node<T>* >(v.begin() + start, v.begin() + end);
	return result;
}
template<class  T  >
vector<T   >  Tree<T>::subList(vector<T  > v, int  start, int end)
{
	vector<T  >  result = vector<T  >(v.begin() + start, v.begin() + end);
	return result;
}
template<class  T >
void Tree<T>::check(vector<T> keys, Node<T>* currentNode)
{
	if (keys.size() > weight - 1) {
		Node<T>* childLeft = new Node<T>();
		Node<T>* childRight = new Node<T>();
		int half = keys.size() / 2;
		vector<T> vl(keys.begin(), keys.begin() + half);
		vector<T> vr(keys.begin() + half + 1, keys.end());
		childLeft->addKey(vl);
		childRight->addKey(vr);
		if (currentNode->getChildren().size() > 0) {
			childLeft->addChildren(subList(currentNode->getChildren(), 0, half + 1));
			childRight->addChildren(subList(currentNode->getChildren(), half + 1, currentNode->getChildren().size()));
		}
		if (currentNode->getParent() == nullptr) {
			Node<T>* n = new Node<T>();
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
template<class  T >
void Tree<T>::searchNode(T value, Node<T>* node, bool search)
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
			findNode = node;
			if (!search) {

				if (node->getParent() == nullptr && node->getKeys().size() == 1 && node->getChildren().size() == 0)
					return;
				checkState(node, value);
			}
			return;
		}
	}
}
template<class  T >
void Tree<T>::checkState(Node<T>* node, T value)
{

	if (node->getChildren().size() == 0) {
		//лист
		int index = node->getIndexFromKeys(value);
		(*(node->getlinkKeys())).erase((*(node->getlinkKeys())).begin() + index);
		if (node->getKeys().size() == 0) {
			checkNearNodes(node);
		}
	}
	else {
		//центральный
		merge(node, value);

	}
}
template<class  T >
void Tree<T>::merge(Node<T>* node, T value)
{
	int index = node->getIndexFromKeys(value);
	node->removeKey(index);
	Node<T>* childLeft = node->getChild(index);
	Node<T>* childRight = node->getChild(index + 1);
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
template<class  T >
void Tree<T>::checkNearNodes(Node<T>* node)
{
	Node<T>* parent = node->getParent();
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
		Node<T>* leftChild = parent->getChild(index - 1);
		T maxValueOfLeftChild = leftChild->getKeys().at(leftChild->getKeys().size() - 1);
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
		Node<T>* rightChild = parent->getChild(index + 1);

		T minValueOfRightChild = rightChild->getKeys().at(0);
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
		Node<T>* n = new Node<T>();
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
