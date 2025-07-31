#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include "BST.h"
#include "AVL.h"
using namespace std;
using namespace std::chrono;

// Replace this code once you have determined that your Trees work as expected
int main() {
    // Test BinaryTree
    cout << "=== Binary Search Tree ===" << endl;
    BST bst;

    for (int i = 0; i < 10; i++) {
        bst.insert(i);
    }

    bst.printPretty();

    cout << "Search 7 in BST: " << (bst.search(7) ? "Found" : "Not found") << endl;
    cout << "Search 11 in BST: " << (bst.search(11) ? "Found" : "Not found") << endl;

    // Test AVL Tree
    cout << "\n=== AVL Tree ===" << endl;
    AVL avl;

    for (int i = 0; i < 10; i++) {
        avl.insert(i);
    }

    avl.printPretty();

    cout << "Search 7 in AVL: " << (avl.search(7) ? "Found" : "Not found") << endl;
    cout << "Search 11 in AVL: " << (avl.search(11) ? "Found" : "Not found") << endl;

    return 0;
}
