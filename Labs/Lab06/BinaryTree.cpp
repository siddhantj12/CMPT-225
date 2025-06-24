#include "BinaryTree.h"

BinaryTree::BinaryTree() : root(nullptr), size(0) {}

void BinaryTree::insert(const std::string& e) {
	Node* newNode = new Node{e, nullptr, nullptr, nullptr};
	if (!root) root = newNode;
	else insertRecursive(root, newNode);
	size++;
}

bool BinaryTree::insertRecursive(Node* curr, Node* newNode) {
	if (!curr->left) {
		curr->left = newNode;
		newNode->parent = curr;
		return true;
	}
	if (!curr->right) {
		curr->right = newNode;
		newNode->parent = curr;
		return true;
	}
	return insertRecursive(curr->left, newNode) ||
	       insertRecursive(curr->right, newNode);
}


// --- Preorder ---
PreorderIterator BinaryTree::begin_pre() const {
	return PreorderIterator(root);
}

PreorderIterator BinaryTree::end_pre() const {
	return PreorderIterator(nullptr);
}

// --- Inorder ---
InorderIterator BinaryTree::begin_in() const {
	return InorderIterator(root);
}

InorderIterator BinaryTree::end_in() const {
	return  InorderIterator(nullptr);
}

// --- Postorder ---
PostorderIterator BinaryTree::begin_post() const {
	return PostorderIterator(root);
}

PostorderIterator BinaryTree::end_post() const {
	return PostorderIterator(nullptr);
}
// In BinaryTree.cpp
