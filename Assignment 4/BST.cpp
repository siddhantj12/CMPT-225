#include <iostream>
#include "BST.h"
using namespace std;

// Default constructor
BST::BST(){
    root = new Node{-1, nullptr, nullptr};
}

// Big Three
// copy constructor 
BST::BST(const BST& other) {
    root = copyTree(other.root);
}
// assignment operator
BST& BST::operator=(const BST& other) {
    if (this != &other){
        deleteTree(root);
        root = copyTree(other.root);
    }
    return *this;
}
// destructor
BST::~BST() {
    deleteTree(root);
}

// Big Three Helpers
// delete tree
void BST::deleteTree(Node* node) {
    if (node == nullptr) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

// copy tree
Node* BST::copyTree(Node* node) {
    if (node == nullptr)
        return nullptr;

    Node* newNode = new Node;
    newNode->key = node->key;

    newNode->left = copyTree(node->left);
    newNode->right = copyTree(node->right);

    return newNode;
}

// Helper functions to print the tree 
void BST::printPretty(Node* node, string prefix, bool isLeft) const{
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
void BST::printPretty() const{
    printPretty(root, "", true);
}

// Testing node placement
bool BST::isExternal(Node* v) const{
    return v->left == nullptr && v->right == nullptr;
}
bool BST::isInternal(Node* v) const{
    return !isExternal(v);
}

// get height of tree 
int BST::getHeight() const {
    return getHeight(root);
}

int BST::getHeight(Node* node) const {
    if (isExternal(node)) {
        return -1;                     // external (dummy) nodes have height -1
    }
    // height is 1 + max of child heights
    int lh = getHeight(node->left);
    int rh = getHeight(node->right);
    return 1 + (lh > rh ? lh : rh);
}

// Searching for keys
Node* BST::treeSearch(int k, Node* v) const{
     if (isExternal(v)) {
        return v;                      // reached dummy leaf
    }
    if (k == v->key) {
        return v;                      // found key
    }
    if (k < v->key) {
        return treeSearch(k, v->left);
    } else {
        return treeSearch(k, v->right);
    }
}
bool BST::search(int val) const{
    return treeSearch(val, root)->key == val;
}

// Inserting key
void BST::insertAtExternal(Node* w, int k){
    w->key = k;
    w->left = new Node{-1, nullptr, nullptr};
    w->right = new Node{-1, nullptr, nullptr};
}
void BST::treeInsert(int k, Node* v) {
    Node* w = treeSearch(k,v);
    if(isExternal(w))
        insertAtExternal(w,k);
}
void BST::insert(int val) {
    treeInsert(val, root);
}