#ifndef POSTORDER_ITERATOR_H
#define POSTORDER_ITERATOR_H

#include "Node.h"
#include <list>
#include <string>

class PostorderIterator {
private:
    std::list<Node*> work;

    void fillPostorder(Node* node) {
        if (!node) return;
        fillPostorder(node->left);
        fillPostorder(node->right);
        work.push_back(node);
    }

public:
    PostorderIterator(Node* root) {
        fillPostorder(root);
    }

    std::string& operator*() const {
        return work.front()->element;
    }

    PostorderIterator& operator++() {
        work.pop_front();
        return *this;
    }

    bool operator!=(const PostorderIterator& other) const {
        if (work.empty() && other.work.empty()) return false;
        if (work.empty() || other.work.empty()) return true;
        return work.front() != other.work.front();
	};
};

#endif