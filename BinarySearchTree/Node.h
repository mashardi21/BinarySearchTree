#ifndef NODE_H
#define NODE_H

template <typename T>
class Node {
public:
	Node() {
		_leftChild = nullptr;
		_rightChild = nullptr;
	}

	Node(T data) {
		_data = data;
		_leftChild = nullptr;
		_rightChild = nullptr;
	}

	void setData(T data) {
		_data = data;
	}

	void setLeftChild(Node<T>* leftChild) {
		_leftChild = leftChild;
	}

	void setRightChild(Node<T>* rightChild) {
		_rightChild = rightChild;
	}

	T getData() {
		return _data;
	}

	Node<T>* getLeftChild() {
		return _leftChild;
	}

	Node<T>* getRightChild() {
		return _rightChild;
	}
private:
	T _data;
	Node<T>* _leftChild;
	Node<T>* _rightChild;
};

#endif // !NODE_H