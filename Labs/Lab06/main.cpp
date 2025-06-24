#include <iostream>
#include "BinaryTree.h"
#include "PreorderIterator.cpp"
#include "InorderIterator.cpp"
#include "PostorderIterator.cpp"

using namespace std;

int main() {
	BinaryTree b;
	b.insert("A");
	b.insert("B");
	b.insert("C");

        // expected output "Preorder: A B C"
	cout << "Preorder: ";
	for (PreorderIterator it = b.begin_pre(); it != b.end_pre(); ++it) {
		cout << *it << " ";
	}
	cout << endl;

	
        // expected output "Inorder: B A C"
	cout << "Inorder: ";
	for (InorderIterator it = b.begin_in(); it != b.end_in(); ++it) {
		cout << *it << " ";
	}
	cout << endl;
	
	
        // expected output "Postorder: B C A"
	cout << "Postorder: ";
	for (PostorderIterator it = b.begin_post(); it != b.end_post(); ++it) {
		cout << *it << " ";
	}
	cout << endl;
	

	return 0;
}