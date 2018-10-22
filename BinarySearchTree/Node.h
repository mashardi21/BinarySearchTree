#ifndef NODE_H
#define NODE_H

template <typename T>
class Node {
public:
	Node() {
		_count = 1;
		_depth = -1;
		_leftChild = nullptr;
		_rightChild = nullptr;
	}

	Node(T data) {
		_data = data;
		_count = 1;
		_depth = -1;
		_leftChild = nullptr;
		_rightChild = nullptr;
	}

	void setData(T data) {
		_data = data;
	}

	void addCount() {
		_count++;
	}

	void subCount() {
		_count--;
	}

	void setDepth(int depth) {
		_depth = depth;
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

	int getCount() {
		return _count;
	}

	int getDepth() {
		return _depth;
	}

	Node<T>* getLeftChild() {
		return _leftChild;
	}

	Node<T>* getRightChild() {
		return _rightChild;
	}
private:
	T _data;
	int _count;
	int _depth;
	Node<T>* _leftChild;
	Node<T>* _rightChild;
};

#endif // !NODE_H