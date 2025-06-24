#ifndef NODE_H
#define NODE_H

#include <string>

struct Node {
	std::string element;
	Node* parent;
	Node* left;
	Node* right;
};

#endif