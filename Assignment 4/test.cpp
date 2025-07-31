// test.cpp
#include <iostream>
#include <cassert>
#include <cmath>
#include "BST.h"
#include "AVL.h"

void testBSTBasics() {
    BST b;

    // 1) Empty tree
    assert(!b.search(0));
    assert(b.getHeight() == -1);

    // 2) Single insert & duplicate
    b.insert(5);
    assert(b.search(5));
    assert(b.getHeight() == 0);      // one node → height 0
    b.insert(5);                     // duplicate
    assert(b.getHeight() == 0);      // no change

    // 3) Multiple inserts / searches
    for (int i = 0; i < 7; ++i) b.insert(i);
    for (int i = 0; i < 7; ++i) assert(b.search(i));
    assert(!b.search(42));

    // 4) Copy constructor
    BST b2(b);
    b.insert(100);
    assert(!b2.search(100));         // deep copy

    // 5) Assignment operator
    BST b3;
    b3 = b;
    b3.insert(200);
    assert(!b.search(200));

    std::cout << "[PASS] BST basic API + Big Three\n";
}

void testAVLBasics() {
    AVL a;

    // 1) Empty tree
    assert(!a.search(0));
    assert(a.getHeight() == 0 || a.getHeight() == -1);

    // 2) Single insert & duplicate
    a.insert(5);
    assert(a.search(5));
    int h1 = a.getHeight();
    a.insert(5);
    assert(a.getHeight() == h1);

    // 3) LL, RR, LR, RL cases (height ≤ 1)
    {
        AVL t;
        t.insert(3); t.insert(2); t.insert(1);   // LL
        assert(t.getHeight() <= 1);
    }
    {
        AVL t;
        t.insert(1); t.insert(2); t.insert(3);   // RR
        assert(t.getHeight() <= 1);
    }
    {
        AVL t;
        t.insert(3); t.insert(1); t.insert(2);   // LR
        assert(t.getHeight() <= 1);
    }
    {
        AVL t;
        t.insert(1); t.insert(3); t.insert(2);   // RL
        assert(t.getHeight() <= 1);
    }

    // 4) Larger sequence: ensure balance bound h ≤ 2*log2(n)+2
    {
        AVL t;
        int n = 15;
        for (int i = 0; i < n; ++i) t.insert(i);
        int h = t.getHeight();
        int bound = int(2*std::log2(n) + 2);
        assert(h <= bound);
        for (int i = 0; i < n; ++i) assert(t.search(i));
        assert(!t.search(999));
    }

    // 5) Copy constructor
    AVL a2(a);
    a.insert(123);
    assert(!a2.search(123));

    // 6) Assignment operator
    AVL a3;
    a3 = a;
    a3.insert(456);
    assert(!a.search(456));

    std::cout << "[PASS] AVL basic API + Big Three\n";
}

int main() {
    testBSTBasics();
    testAVLBasics();
    std::cout << ">>> All tests passed! 🎉\n";
    return 0;
}
