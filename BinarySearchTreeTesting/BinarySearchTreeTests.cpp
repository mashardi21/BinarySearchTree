#include <iostream>

#include "catch.hpp"
#include "BinarySearchTree.h"

TEST_CASE("Create a BinarySearchTree Object/Data type of int/Depth = -1", "[Creation]") {
	BinarySearchTree<int> tree;

	REQUIRE(tree.getRootPtr() == nullptr);
	REQUIRE(tree.getTreeDepth() == -1);
}

TEST_CASE("insertNode/insert a node in the correct location on the tree/depth updates, node is added to the tree int the correct location", "[Insertion]") {
	BinarySearchTree<int> tree;

	SECTION("insertNode/attempt to insert NULL instead of a valid node/the function should do nothing") {
		tree.insertNode(tree.getRootPtr(), NULL);

		REQUIRE(tree.getRootPtr() == nullptr);
		REQUIRE(tree.getTreeDepth() == -1);
	}


	tree.insertNode(tree.getRootPtr(), 5);

	SECTION("insertNode/insert a node into an empty tree/depth = 0, rootptr is set to the new node") {
		REQUIRE(tree.getRootPtr() != nullptr);
		REQUIRE(tree.getTreeDepth() == 0);
	}

	SECTION("insertNode/insert a node into a tree that only contains the root, the new node is less than the root/depth = 1, the left child of the root node becomes the new node, right child remains nullptr") {
		tree.insertNode(tree.getRootPtr(), 2);

		REQUIRE(tree.getTreeDepth() == 1);
		REQUIRE(tree.getRootPtr()->getLeftChild() != nullptr);
		REQUIRE(tree.getRootPtr()->getLeftChild()->getData() == 2);
	}

	SECTION("insertNode/insert a node into a tree that only contains the root, the new node is greater than the root/depth = 1, the right child of the root node becomes the new node, left child remains nullptr") {
		tree.insertNode(tree.getRootPtr(), 7);

		REQUIRE(tree.getTreeDepth() == 1);
		REQUIRE(tree.getRootPtr()->getRightChild() != nullptr);
		REQUIRE(tree.getRootPtr()->getRightChild()->getData() == 7);
	}

	SECTION("insertNode/insert a node into a tree where the root already has two children, the new node is less than the root and the left child/depth = 2, the left child of the root's left child becomes the new node") {
		tree.insertNode(tree.getRootPtr(), 3);
		tree.insertNode(tree.getRootPtr(), 2);

		REQUIRE(tree.getTreeDepth() == 2);
		REQUIRE(tree.getRootPtr()->getLeftChild()->getLeftChild() != nullptr);
		REQUIRE(tree.getRootPtr()->getLeftChild()->getLeftChild()->getData() == 2);
		REQUIRE(tree.getRootPtr()->getLeftChild()->getRightChild() == nullptr);
	}

	SECTION("insertNode/insert a node into a tree where the root already has two children, the new node is less than the root and greater than the left child/depth = 2, the right child of the root's left child becomes the new node") {
		tree.insertNode(tree.getRootPtr(), 3);
		tree.insertNode(tree.getRootPtr(), 4);

		REQUIRE(tree.getTreeDepth() == 2);
		REQUIRE(tree.getRootPtr()->getLeftChild()->getRightChild() != nullptr);
		REQUIRE(tree.getRootPtr()->getLeftChild()->getRightChild()->getData() == 4);
		REQUIRE(tree.getRootPtr()->getLeftChild()->getLeftChild() == nullptr);
	}

	SECTION("insertNode/insert a node into a tree where the root already has two children, the new node is greater than the root and less than the left child/depth = 2, the left child of the root's right child becomes the new node") {
		tree.insertNode(tree.getRootPtr(), 7);
		tree.insertNode(tree.getRootPtr(), 6);

		REQUIRE(tree.getTreeDepth() == 2);
		REQUIRE(tree.getRootPtr()->getRightChild()->getLeftChild() != nullptr);
		REQUIRE(tree.getRootPtr()->getRightChild()->getLeftChild()->getData() == 6);
		REQUIRE(tree.getRootPtr()->getRightChild()->getRightChild() == nullptr);
	}

	SECTION("insertNode/insert a node into a tree where the root already has two children, the new node is greater than the root and the left child/depth = 2, the right child of the root's right child becomes the new node") {
		tree.insertNode(tree.getRootPtr(), 7);
		tree.insertNode(tree.getRootPtr(), 8);

		REQUIRE(tree.getTreeDepth() == 2);
		REQUIRE(tree.getRootPtr()->getRightChild()->getRightChild() != nullptr);
		REQUIRE(tree.getRootPtr()->getRightChild()->getRightChild()->getData() == 8);
		REQUIRE(tree.getRootPtr()->getRightChild()->getLeftChild() == nullptr);
	}

	SECTION("insertNode/insert a node that contains a value already stored in the tree/depth should remain unchanged, the count value of the node in the tree should increment by 1") {
		int currentDepth = tree.getTreeDepth();
		int currentCount = tree.getRootPtr()->getCount();

		tree.insertNode(tree.getRootPtr(), 5);

		REQUIRE(tree.getTreeDepth() == currentDepth);
		REQUIRE(tree.getRootPtr()->getCount() == currentCount + 1);
	}
}

TEST_CASE("findNode/find the node that contains a given value/return a pointer to the found node, capable of searching through multiple layers of the tree", "[Searching]") {
	BinarySearchTree<int> tree;

	SECTION("findNode/search for a node in an empty tree/the function should return nullptr") {
		REQUIRE(tree.findNode(tree.getRootPtr(), 5) == nullptr);
	}

	tree.insertNode(tree.getRootPtr(), 5);
	tree.insertNode(tree.getRootPtr(), 3);
	tree.insertNode(tree.getRootPtr(), 7);
	tree.insertNode(tree.getRootPtr(), 2);
	tree.insertNode(tree.getRootPtr(), 4);
	tree.insertNode(tree.getRootPtr(), 6);
	tree.insertNode(tree.getRootPtr(), 8);

	SECTION("findNode/search for NULL instead of a real value/the function should return nullptr") {
		REQUIRE(tree.findNode(tree.getRootPtr(), NULL) == nullptr);
	}

	SECTION("findNode/search for the root node's value/the function should return a pointer to the root node") {
		REQUIRE(tree.findNode(tree.getRootPtr(), 5) == tree.getRootPtr());
	}

	SECTION("findNode/search for the left child of the root/the function should return a pointer to the left child of the root node") {
		REQUIRE(tree.findNode(tree.getRootPtr(), 3) == tree.getRootPtr()->getLeftChild());
	}

	SECTION("findNode/search for the right child of the root/the function should return a pointer to the right child of the root node") {
		REQUIRE(tree.findNode(tree.getRootPtr(), 7) == tree.getRootPtr()->getRightChild());
	}

	SECTION("findNode/search for the far left grandchild of the root node/ the function should return a pointer to the left child of the root's left child") {
		REQUIRE(tree.findNode(tree.getRootPtr(), 2) == tree.getRootPtr()->getLeftChild()->getLeftChild());
	}

	SECTION("findNode/search for the right child of the left child of the root node/ the function should return a pointer to the right child of the root's left child") {
		REQUIRE(tree.findNode(tree.getRootPtr(), 4) == tree.getRootPtr()->getLeftChild()->getRightChild());
	}

	SECTION("findNode/search for the left child of the right child of the root node/ the function should return a pointer to the left child of the root's right child") {
		REQUIRE(tree.findNode(tree.getRootPtr(), 6) == tree.getRootPtr()->getRightChild()->getLeftChild());
	}

	SECTION("findNode/search for the far right grandchild of the root node/ the function should return a pointer to the right child of the root's right child") {
		REQUIRE(tree.findNode(tree.getRootPtr(), 8) == tree.getRootPtr()->getRightChild()->getRightChild());
	}
}

TEST_CASE("deleteNode/delete a node from the tree/depth updates if neccessary, if the node to be deleted has children, update the tree accordingly", "[Deletion]") {
	BinarySearchTree<int> tree;

	SECTION("deleteNode/delete a node from an empty tree/this function should return false") {
		REQUIRE(!(tree.deleteNode(tree.getRootPtr(), 2)));
	}

	tree.insertNode(tree.getRootPtr(), 5);
	tree.insertNode(tree.getRootPtr(), 3);
	tree.insertNode(tree.getRootPtr(), 7);
	tree.insertNode(tree.getRootPtr(), 2);

	SECTION("deleteNode/delete a leaf node from the tree when that node is the only node at that depth/depth decrements by 1, the node should be removed, the corresponding child of the node's parent shoudl be set to nullptr") {
		int currentDepth = tree.getTreeDepth();
		
		tree.deleteNode(tree.getRootPtr(), 2);

		REQUIRE(tree.getTreeDepth() == currentDepth - 1);
		REQUIRE(tree.findNode(tree.getRootPtr(), 2) == nullptr);
	}

	tree.insertNode(tree.getRootPtr(), 4);
	tree.insertNode(tree.getRootPtr(), 6);

	SECTION("deleteNode/delete a leaf node from a tree when there are other nodes at that depth/ depth doesn't change/ the node should be removed from the tree") {
		int currentDepth = tree.getTreeDepth();

		tree.deleteNode(tree.getRootPtr(), 2);

		REQUIRE(tree.getTreeDepth() == currentDepth);
		REQUIRE(tree.findNode(tree.getRootPtr(), 2) == nullptr);
	}

	SECTION("deleteNode/delete a node with only one child/depth updates if neccessary, the node should be removed from the tree, the child node becomes the child of the deleted node's parent") {
		tree.deleteNode(tree.getRootPtr(), 7);

		REQUIRE(tree.getRootPtr()->getRightChild() != nullptr);
		REQUIRE(tree.getRootPtr()->getRightChild()->getData() == 6);
	}

	tree.insertNode(tree.getRootPtr(), 9);
	tree.insertNode(tree.getRootPtr(), 8);

	SECTION("deleteNode/delete a node that has two children/depth decrements by 1, the node shoudl be removed from the tree, the next highest value node replaces the deleted node") {
		int currentDepth = tree.getTreeDepth();
		
		tree.deleteNode(tree.getRootPtr(), 7);

		REQUIRE(tree.getTreeDepth() == currentDepth - 1);
		REQUIRE(tree.getRootPtr()->getRightChild()->getData() == 8);
	}

	SECTION("clearTree/clear the tree/delete all nodes without deleting the tree object itself, depth = -1, rootPtr = nullptr") {
		tree.clearTree(tree.getRootPtr());

		REQUIRE(tree.getTreeDepth() == -1);
		REQUIRE(tree.getRootPtr() == nullptr);
	}
}