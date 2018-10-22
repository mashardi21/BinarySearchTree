#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include "Node.h"

template<typename T>
class BinarySearchTree {
public:
	// Default constructor
	BinarySearchTree() {
		_treeDepth = -1;
		_rootPtr = nullptr;
	}

	// Destructor
	~BinarySearchTree() {
		destroyTree(_rootPtr);
	}

	// This function inserts a node into the BST
	void insertNode(Node<T>* startNode,T newData) {
		// if the data is null, don't do anything
		if (!newData) {
			return;
		}

		// insert the new node as the root if the list is empty
		if (_rootPtr == nullptr) {
			Node<T>* newNode = new Node<T>(newData);
			newNode->setDepth(0);
			_rootPtr = newNode;
		}
		else {
			// If the current node containts the same data as what is being added, add 1 to the count for that node
			if (newData == startNode->getData()) {
				startNode->addCount();
			}
			// Iterate through the nodes calling insertNode recursively until the correct position for the new node is found
			// Then add the node in that position
			else if (newData < startNode->getData()) {
				if (startNode->getLeftChild() == nullptr) {
					Node<T>* newNode = new Node<T>(newData);
					newNode->setDepth(startNode->getDepth() + 1);
					startNode->setLeftChild(newNode);
				}
				else {
					insertNode(startNode->getLeftChild(), newData);
				}
			}
			else if (newData > startNode->getData()) {
				if (startNode->getRightChild() == nullptr) {
					Node<T>* newNode = new Node<T>(newData);
					newNode->setDepth(startNode->getDepth() + 1);
					startNode->setRightChild(newNode);
				}
				else {
					insertNode(startNode->getRightChild(), newData);
				}
			}
		}

	}

	// This function is called recursively to delete the node containing the given value and then returns true or false based of whether a node was deleted or not
	bool deleteNode(Node<T>* startNode, T dataToDelete) {

		// if the list is empty, don't do anything
		if (_rootPtr == nullptr) {
			return false;
		}

		// If the given data is null, don't do anything
		if (!dataToDelete) {
			return false;
		}
		// If the root node needs to be deleted, delete it
		else if (dataToDelete == startNode->getData()) {
			// If there are 0 or 1 children of the root
			if (startNode->getLeftChild() == nullptr) {
				_rootPtr = startNode->getRightChild();
				delete startNode;
				return true;
			}
			else if (startNode->getRightChild() == nullptr) {
				_rootPtr = startNode->getLeftChild();
				delete startNode;
				return true;
			}
			// If there are 2 children of the root
			else {
				Node<T>* temp = findNextHighestNode(_rootPtr->getRightChild());
				_rootPtr->setData(temp->getData());
				 return deleteNode(_rootPtr->getRightChild(), temp->getData());
			}
		}
		// This section is identical to deleting the root, except it first iterates through the list to find the correct node to delete
		// if the node to be deleted is less than the current node being examined
		else if (dataToDelete < startNode->getData()) {
			if (startNode->getLeftChild() != nullptr) {
				if (dataToDelete == startNode->getLeftChild()->getData()) {
					if (startNode->getLeftChild()->getLeftChild() == nullptr) {
						Node<T>* tempNode = startNode->getLeftChild()->getRightChild();
						delete startNode->getLeftChild();
						startNode->setLeftChild(tempNode);
						return true;
					}
					else if (startNode->getLeftChild()->getRightChild() == nullptr) {
						Node<T>* tempNode = startNode->getLeftChild()->getLeftChild();
						delete startNode->getLeftChild();
						startNode->setLeftChild(tempNode);
						return true;
					}
					else {
						Node<T>* temp = findNextHighestNode(startNode->getLeftChild()->getRightChild());
						startNode->getLeftChild()->setData(temp->getData());
						return deleteNode(startNode->getLeftChild()->getRightChild(), temp->getData());
					}
				}
				else {
					return deleteNode(startNode->getLeftChild(), dataToDelete); // recursive call to keep iterating through the tree
				}
			}
		}
		// This section is identical to deleting the root, except it first iterates through the list to find the correct node to delete
		// if the node to be deleted is greater than the current node being examined
		else if (dataToDelete > startNode->getData()) {
			if (startNode->getRightChild() != nullptr) {
				if (dataToDelete == startNode->getRightChild()->getData()) {
					if (startNode->getRightChild()->getLeftChild() == nullptr) {
						Node<T>* tempNode = startNode->getRightChild()->getLeftChild();
						delete startNode->getRightChild();
						startNode->setRightChild(tempNode);
						return true;
					}
					else if (startNode->getRightChild()->getRightChild() == nullptr) {
						Node<T>* tempNode = startNode->getRightChild()->getLeftChild();
						delete startNode->getRightChild();
						startNode->setRightChild(tempNode);
						return true;
					}
					else {
						Node<T>* temp = findNextHighestNode(startNode->getRightChild()->getRightChild());
						startNode->getRightChild()->setData(temp->getData());
						return deleteNode(startNode->getRightChild()->getRightChild(), temp->getData());
					}
				}
				else {
					return deleteNode(startNode->getRightChild(), dataToDelete); // recursive call to keep iterating through the tree
				}
			}
		}

		return false;
	}

	// This function calls itself recursively to delete every node including and below a given node
	void clearTree(Node<T>* startNode) {
		if (_rootPtr == nullptr) {
			return;
		}

		deleteNode(_rootPtr, startNode->getData());

		clearTree(_rootPtr); // recursive call to keep iterating through the tree
	}

	// This function calls itself recursively to find the next highest node when given the right-hand child of
	// the node for which the next highest node is being found for
	Node<T>* findNextHighestNode(Node<T>* startNode) {
		if (startNode->getLeftChild() == nullptr) {
			return startNode;
		}

		findNextHighestNode(startNode->getLeftChild()); // recursive call to keep iterating through the tree
	}

	// This function calls itself recursively to search through the tree for a node containing a given value
	Node<T>* findNode(Node<T>* startNode, T dataToFind) {
		if (_rootPtr == nullptr) {
			return nullptr;
		}

		if (!dataToFind) {
			return nullptr;
		}
		else if (dataToFind == startNode->getData()) {
			return startNode;
		}
		else if (dataToFind < startNode->getData()) {
			if (startNode->getLeftChild() != nullptr) {
				if (dataToFind == startNode->getLeftChild()->getData()) {
					return startNode->getLeftChild();
				}
				else {
					return findNode(startNode->getLeftChild(), dataToFind); // recursive call to keep iterating through the tree
				}
			}
		}
		else if (dataToFind > startNode->getData()) {
			if (startNode->getRightChild() != nullptr) {
				if (dataToFind == startNode->getRightChild()->getData()) {
					return startNode->getRightChild();
				}
				else {
					return findNode(startNode->getRightChild(), dataToFind); // recursive call to keep iterating through the tree
				}
			}
		}
		
		return nullptr;
	}

	Node<T>* findMax() {

	}

	// This function calls istelf recursively to determine the depth of the BST
	// if the list is empty, the depth is -1
	int findTreeDepth(Node<T>* startNode) {
		if (startNode == nullptr) {
			return -1;
		}

		int left = findTreeDepth(startNode->getLeftChild());
		int right = findTreeDepth(startNode->getRightChild());

		if (left > right) {
			return left + 1;
		}
		else {
			return right + 1;
		}
	}

	// This function returns the current depth of the tree
	int getTreeDepth() {
		_treeDepth = findTreeDepth(_rootPtr);
		
		return _treeDepth;
	}

	// Getter for _rootptr
	Node<T>* getRootPtr() {
		return _rootPtr;
	}

private:
	int _treeDepth; // Stores the depth of the tree
	Node<T>* _rootPtr; // A pointer to the root node of the tree

	// This function recursively traverses the tree, deleting leaf nodes until the entire tree has been destroyed
	// It is private to ensure it is only called by the desructor
	void destroyTree(Node<T>* node) {
		if (node) {
			destroyTree(node->getLeftChild());
			destroyTree(node->getRightChild());
			delete node;
		}
	}
};

#endif // !BINARYSEARCHTREE_H
