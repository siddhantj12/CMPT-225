#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include "Node.h"
#include "PreorderIterator.cpp"
#include "PostorderIterator.cpp"
#include "InorderIterator.cpp"

class BinaryTree {
private:
	Node* root;
	int size;
	bool insertRecursive(Node* curr, Node* newNode);

public:
	BinaryTree();
	void insert(const std::string& e);

	PreorderIterator begin_pre() const;
	PostorderIterator begin_post() const;
	InorderIterator begin_in() const;

	PreorderIterator end_pre() const;
	PostorderIterator end_post() const;
	InorderIterator end_in() const;
};

#endif
