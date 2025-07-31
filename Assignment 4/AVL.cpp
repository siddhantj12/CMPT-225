#include <iostream>
#include "AVL.h"
using namespace std;

// Default constructor
AVL::AVL(){
    root = new NodeAVL{-1, 0, nullptr, nullptr, nullptr};
}

// Big Three
// copy constructor 
AVL::AVL(const AVL& other) {
    root = copyTree(other.root);
}
// assignment operator
AVL& AVL::operator=(const AVL& other) {
    if (this != &other){
        deleteTree(root);
        root = copyTree(other.root);
    }
    return *this;
}
// destructor
AVL::~AVL() {
    deleteTree(root);
}

// Big Three Helpers
// delete tree
void AVL::deleteTree(NodeAVL* node) {
    if (node == nullptr) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

// copy tree
NodeAVL* AVL::copyTree(NodeAVL* node, NodeAVL* parent) {
    if (node == nullptr)
        return nullptr;

    NodeAVL* newNode = new NodeAVL;
    newNode->key = node->key;
    newNode->height = node->height;
    newNode->parent = parent;

    newNode->left = copyTree(node->left, newNode);
    newNode->right = copyTree(node->right, newNode);

    return newNode;
}

// Helper functions to print the tree 
void AVL::printPretty(NodeAVL* node, string prefix, bool isLeft) const{
    if (node == nullptr || isExternal(node)) 
        return;

    if (node->right != nullptr && isInternal(node->right)) {
        printPretty(node->right, prefix + (isLeft ? "│   " : "    "), false);
    }

    cout << prefix;
    cout << (isLeft ? "└── " : "┌── ");
    cout << node->key << endl;

    if (node->left != nullptr && isInternal(node->left)) {
        printPretty(node->left, prefix + (isLeft ? "    " : "│   "), true);
    }
}
void AVL::printPretty() const{
    printPretty(root, "", true);
}



// Testing node placement
bool AVL::isExternal(NodeAVL* v) const{
    return v->left == nullptr && v->right == nullptr;
}
bool AVL::isInternal(NodeAVL* v) const{
    return !isExternal(v);
}

// get height of tree
int AVL::getHeight() const {
    return root->height;
}

// Searching for keys
NodeAVL* AVL::treeSearch(int k, NodeAVL* v) const{
     if (isExternal(v)) {
        return v;                     // reached dummy leaf
    }
    if (k == v->key) {
        return v;                     // found key
    }
    if (k < v->key) {
        return treeSearch(k, v->left);
    } else {
        return treeSearch(k, v->right);
    }
}
bool AVL::search(int val) const{
    return treeSearch(val, root)->key == val;
}


// Inserting key
void AVL::insertAtExternal(NodeAVL* w, int k){
    w->key = k;
    w->height = 1;
    w->left = new NodeAVL{-1, 0, nullptr, nullptr, w};
    w->right = new NodeAVL{-1, 0, nullptr, nullptr, w};
}

void AVL::treeInsert(int k, NodeAVL* v) {
    NodeAVL* w = treeSearch(k,v);
    if(isExternal(w)){ // do not duplicate 
        insertAtExternal(w,k);
        rebalance(w);
    }
}

void AVL::insert(int val) {
    treeInsert(val, root);
}


// AVL tools for rotations
void AVL::setHeight(NodeAVL* v){
    v->height = 1 + (v->left->height > v->right->height ? v->left->height : v->right->height);
}

void AVL::rebalance(NodeAVL* v){
    NodeAVL* z = v;
    while(z != root){
        z = z->parent;
        // update height 
        setHeight(z);
        // check if balanced
        int balanceFactor = z->left->height - z->right->height;
        if(balanceFactor < -1 || 1 < balanceFactor){
            // find y
            NodeAVL* y = z->left->height > z->right->height ? z->left : z->right;
            // find x
            NodeAVL* x = y->left->height > y->right->height ? y->left : y->right;
            restructure(z, y, x);
            setHeight(x);
            setHeight(y);
            setHeight(z);
        }
    }
}

void AVL::restructure(NodeAVL* z, NodeAVL* y, NodeAVL* x){
    if (y == z->left) {
        // left-heavy
        if (x == y->left) {
            // LL case
            rightRotation(z);
        } else {
            // LR case
            leftRotation(y);
            rightRotation(z);
        }
    } else {
        // right-heavy
        if (x == y->right) {
            // RR case
            leftRotation(z);
        } else {
            // RL case
            rightRotation(y);
            leftRotation(z);
        }
    }
}

void AVL::leftRotation(NodeAVL* x){
    NodeAVL* y = x->right;
    NodeAVL* b = y->left;

    // detach b from y, link to x
    x->right = b;
    if (b) b->parent = x;

    // y moves up to x's position
    y->parent = x->parent;
    if (x->parent == nullptr) {
        root = y;
    } else if (x->parent->left == x) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }

    // complete rotation
    y->left = x;
    x->parent = y;
}

void AVL::rightRotation(NodeAVL* x){
    NodeAVL* y = x->left;
    NodeAVL* b = y->right;

    // detach b from y, link to x
    x->left = b;
    if (b) b->parent = x;

    // y moves up to x's position
    y->parent = x->parent;
    if (x->parent == nullptr) {
        root = y;
    } else if (x->parent->left == x) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
     // complete rotation
    y->right = x;
    x->parent = y;

}