#include <iostream>
#include <vector>
using namespace std;

struct Node {
  vector<int> keys;
  vector<Node *> children;
  Node *parent;
};

class TwoFour {
private:
  Node *root;

  bool isExternal(Node *v) { return v->children.empty(); }
  bool isInternal(Node *v) { return !isExternal(v); }

  bool contains(Node *v, int k) {
    for (int key : v->keys) {
      if (key == k)
        return true;
    }
    return false;
  }

  Node *treeSearch(int k, Node *v) {
    if (isExternal(v))
      return v;

    for (int i = 0; i < (int)v->keys.size(); i++) {
      if (k == v->keys[i])
        return v;
      if (k < v->keys[i])
        return treeSearch(k, v->children[i]);
    }
    return treeSearch(k, v->children[v->keys.size()]);
  }

  // Add a key k and a new child c to the
  // the parent p. Key k will be inserted
  // in the correct order placment
  void addKey(Node *p, Node *c, int k) {
    int i = p->keys.size() - 1;

    // extend vectors
    p->keys.push_back(0);
    p->children.push_back(nullptr);

    // shift all keys and children
    while (i >= 0 && p->keys[i] > k) {
      p->keys[i + 1] = p->keys[i];
      p->children[i + 2] = p->children[i + 1];
      i--;
    }

    // add key and child
    p->keys[i + 1] = k;
    p->children[i + 2] = c;
    if (c != nullptr)
      c->parent = p;
  }

  // IMPLEMENT THIS FUNCTION
  void splitChild(Node *parent, Node *child) {
    // YOUR CODE HERE
     // 1. Extract the median (k3) from the overflowed child
    int medianIndex = 2;
    int medianKey = child->keys[medianIndex];

    // 2. Create a new node to hold k4 (and v4,v5 if internal)
    Node *newNode = new Node;
    newNode->parent = parent;
    // move the last key (k4)
    newNode->keys.push_back(child->keys[3]);

    // if child was internal, move its last two children (v4,v5)
    if (!child->children.empty()) {
      newNode->children.push_back(child->children[3]);
      newNode->children.push_back(child->children[4]);
      newNode->children[0]->parent = newNode;
      newNode->children[1]->parent = newNode;
    }

    // 3. Shrink the original child to keep only k1,k2 (and v1–v3 if internal)
    child->keys.resize(2);
    if (!child->children.empty())
      child->children.resize(3);

    // 4. Insert medianKey into parent along with the newNode as its right sibling
    addKey(parent, newNode, medianKey);
  }

  void treeInsert(int k) {
    // find place to add key
    Node *v = treeSearch(k, root);

    // duplicate do not add
    if (!isExternal(v))
      return;

    // since we are adding a new key, we
    // need a new dummy child
    Node *dummy = new Node;
    dummy->parent = v;

    // special case, tree is empty right now
    if (v == root && isExternal(v)) {
      root->children.push_back(dummy);
    } else {
      v = v->parent;
    }

    // add key and new child to node
    addKey(v, dummy, k);

    // did we overflow?
    // if yes, split nodes and give key to parent
    // repeat if parent overflowed too
    while (v != root && (int)v->keys.size() == 4) {
      // split the overflowed node
      splitChild(v->parent, v);
      v = v->parent;
    }

    // if we overflowed the root, we need
    // to make a new root
    if (v == root && (int)v->keys.size() == 4) {
      Node *newRoot = new Node;
      newRoot->parent = nullptr;
      newRoot->children.push_back(root);
      root->parent = newRoot;
      splitChild(newRoot, root);
      root = newRoot;
    }
  }

public:
  TwoFour() {
    root = new Node;
    root->parent = nullptr;
  }

  void insert(int val) { treeInsert(val); }

  bool search(int val) { return isInternal(treeSearch(val, root)); }

  void print() {

    vector<Node *> currLevel{root};
    int level = 0;

    while (!currLevel.empty()) {
      cout << "Level " << level << ": ";
      vector<Node *> nextLevel;

      for (Node *node : currLevel) {
        cout << "[";
        for (int i = 0; i < (int)node->keys.size(); i++) {
          cout << node->keys[i];
          if (i != (int)node->keys.size() - 1)
            cout << " ";
        }
        cout << "] ";

        for (Node *child : node->children) {
          if (child)
            nextLevel.push_back(child);
        }
      }

      cout << endl;
      currLevel = nextLevel;
      level++;
    }
  }

  // Big Three should be included
  // but omitted for simplicity
};

// Example usage
int main() {
  TwoFour tree;
  for (int i = 1; i <= 25; i++) {
    tree.insert(rand() % 1000);
  }
  tree.print();

  return 0;
}
   