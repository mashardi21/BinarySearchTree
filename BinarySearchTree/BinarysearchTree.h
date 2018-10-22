#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include "Node.h"

template<typename T>
class BinarySearchTree {
public:
	BinarySearchTree() {
		_treeDepth = 0;
		_rootPtr = nullptr;
	}

	~BinarySearchTree() {

	}

	void insertNode(T newData) {

	}

	void deleteNode(Node<T>* delNode) {

	}

	void clearTree() {

	}

	Node<T>* findNode(T dataToFind) {

	}

	Node<T>* findMax() {

	}

private:
	int _treeDepth;
	Node<T>* _rootPtr;
};

#endif // !BINARYSEARCHTREE_H
