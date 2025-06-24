#ifndef INORDER_ITERATOR_H
#define INORDER_ITERATOR_H

#include "Node.h"
#include <list>
#include <string>

class InorderIterator {
private:
    std::list<Node*> work;

    void fillInorder(Node* node) {
        if (!node) return;
        fillInorder(node->left);
        work.push_back(node);
        fillInorder(node->right);
    }

public:
    InorderIterator(Node* root) {
        fillInorder(root);
    }

    std::string& operator*() const {
        return work.front()->element;
    }

    InorderIterator& operator++() {
        work.pop_front();
        return *this;
    }

    bool operator!=(const InorderIterator& other) const {
        if (work.empty() && other.work.empty()) return false;
        if (work.empty() || other.work.empty()) return true;
        return work.front() != other.work.front();
    }
};

#endif