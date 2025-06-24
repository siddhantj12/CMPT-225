#ifndef PREORDER_ITERATOR_H
#define PREORDER_ITERATOR_H

#include "Node.h"
#include <list>
#include <string>

class PreorderIterator {
private:
	std::list<Node*> work;

	void fillPreorder(Node* node) {
		if (!node) return;
		work.push_back(node);
		fillPreorder(node->left);
		fillPreorder(node->right);
	}

public:
	PreorderIterator(Node* root) {
		fillPreorder(root);
	}

	std::string& operator*() const {
		return work.front()->element;
	}

	PreorderIterator& operator++() {
		work.pop_front();
		return *this;
	}

	bool operator!=(const PreorderIterator& o) const {
		if (work.empty() && o.work.empty()) return false;
		if (work.empty() || o.work.empty()) return true;
		return work.front() != o.work.front();
	}
};

#endif
